import time


class PumpStep:
    def __init__(self, duration_s: float = 0.0, turn_per_sec: float = 0.0):
        self.duration_s = duration_s
        self.turn_per_sec = turn_per_sec

    def string(self) -> str:
        return f"{self.duration_s:.1f}s @ {self.turn_per_sec:.5f}T/s"

    def _dirFromSpeed(self, val: float) -> bool:
        return val < 0

    def dir(self) -> bool:
        """returns the "direction" of the pump. True means "CCW" in modbus terms."""
        return self._dirFromSpeed(self.turn_per_sec)

    def turns(self) -> float:
        """Returns turns made in action."""
        return (
            self.duration_s * self.turn_per_sec if self.turn_per_sec != 0 else 0.0
        )  # s * (T/s)

    def rpm(self) -> float:
        """Returns rotations per minute."""
        return self.turn_per_sec * 60


class PumpDataProcess:
    def __init__(self, vol_per_turn_ul: float):
        self.vol_per_turn_ul = vol_per_turn_ul

    def create_pump_step(self, flowrate_ul_min: float, vol_ul: float):
        flowrate_per_sec = flowrate_ul_min / 60
        duration_s = abs(vol_ul / flowrate_per_sec)
        turns = vol_ul / self.vol_per_turn_ul
        turn_per_sec = turns / duration_s
        step = PumpStep(duration_s, turn_per_sec)
        return step

    def gen_pump_steps_list(self, *steps):
        recipe = [
            self.create_pump_step(flowrate_ul_min, vol_ul)
            for flowrate_ul_min, vol_ul in steps
        ]

        # Print the contents of the pump_steps_list
        print("\nPump Steps List:")
        for i, step in enumerate(recipe, start=1):
            print(
                f"Step {i} - Duration: {step.duration_s:.2f} seconds, Turn Rate: {step.turn_per_sec:.2f} turns per second"
            )

        return recipe

    def interpretStep(self, step: PumpStep) -> tuple[float, float]:
        """returns the step as total uL transferred (with sign) and flowrate in uL/min."""
        if step.turn_per_sec == 0:
            return 0.0, 0.0

        vol_per_turn = self.vol_per_turn_ul
        vol = vol_per_turn * step.turns()  # [uL/T] * [T] = uL
        flowrate = step.rpm() * vol_per_turn  # [T/min] * [uL/T] = uL / min
        return vol, flowrate


class Routine:
    def __init__(self, pump_steps_list: list[PumpStep] = None, iterations: int = 0):
        self.steps = pump_steps_list
        self.iterations = iterations
        self.step_idx = -1
        self.start_time = 0.0
        self.timer_duration = 0.0

    def iterationsCompleted(self):
        return self.step_idx // len(self.steps)

    def currentIndex(self) -> int:
        return self.step_idx % len(self.steps)

    def len(self) -> int:
        return len(self.steps)

    def currentAction(self) -> PumpStep | None:
        if self.isDone() or self.step_idx == -1:  # Done or not yet started.
            return None
        return self.steps[self.step_idx % len(self.steps)]

    def schedActionOrNone(self) -> PumpStep | None:
        """Returns new action if it is time to start new action, otherwise None."""
        if not self.newActionDue() or self.isDone():
            return None

        self.step_idx += 1
        if self.step_idx != 0 and self.step_idx % len(self.steps) == 0:
            if self.iterationsCompleted() == self.iterations:
                return None  # Done!

        action = self.currentAction()
        self.setTimer(action.duration_s)
        return action

    def isDone(self):
        """Returns True if routine is done."""
        if self.steps is None or len(self.steps) == 0:
            return True  # Early return for no steps found.
        if self.iterations == -1:
            return False  # Early return for infinite iterations.
        iterationsDone = self.iterationsCompleted() >= self.iterations
        # We are not done until current action is done.
        return iterationsDone

    def setTimer(self, duration: float):
        self.start_time = time.time()
        self.timer_duration = duration

    def elapsed(self) -> float:
        """Returns amount of time elapsed since start of current action."""
        return time.time() - self.start_time

    def untilNext(self) -> float:
        """Returns the time in seconds until next action is due.
        Will return a negative number if current action is done."""
        return self.timer_duration - self.elapsed()

    def newActionDue(self):
        """
        Returns True if it is time to start new action with call to update.
        """
        return self.untilNext() <= 0


class RoutineProcessor:
    def __init__(self, routine: Routine, id: int):
        self.r = routine
        self.id = id

    def update(self):
        finished = self.r.isDone()
        print(f"Finish state of routine number {self.id}: ", finished)
        if not finished:
            action = self.r.schedActionOrNone()
            if action == None:
                return
            print(f"New action! {action.string()} until-next={self.r.untilNext():.1f}s")
            vol, flowrate = pdp.interpretStep(action)
            print(
                f"sequences completed: {self.r.iterationsCompleted()}, index: {self.r.currentIndex() + 1} / {self.r.len()}, "
                f"vol: {vol:.0f}uL, flowrate: {flowrate:.1f}uL/min, turns: {action.turns():.3f}, "
                f"velocity: {action.turn_per_sec:.1e}T/s, untilnext: {self.r.untilNext():.1f}s"
            )


pump1_flag = True
pump2_flag = False
pump3_flag = False

# test
if __name__ == "__main__":
    pdp = PumpDataProcess(vol_per_turn_ul=100)
    if pump1_flag:
        pump_steps_list1 = pdp.gen_pump_steps_list(
            (4000, 200),  # flowrate_ul_min, vol_ul
            (4000, 200),
            (4000, 200),
        )
        r1 = Routine(pump_steps_list1, iterations=1)
        pr1 = RoutineProcessor(r1, 1)

    if pump2_flag:
        pump_steps_list2 = pdp.gen_pump_steps_list(
            (4000, 400),  # flowrate_ul_min, vol_ul
            (4000, 400),
            (4000, 400),
        )
        r2 = Routine(pump_steps_list2, iterations=1)
        pr2 = RoutineProcessor(r2, 2)

    if pump3_flag:
        pump_steps_list3 = pdp.gen_pump_steps_list(
            (4000, 600),  # flowrate_ul_min, vol_ul
            (4000, 600),
            (4000, 600),
        )
        r3 = Routine(pump_steps_list3, iterations=1)
        pr3 = RoutineProcessor(r3, 2)

    while True:
        if pump1_flag:
            pr1.update()
        if pump2_flag:
            pr2.update()
        if pump3_flag:
            pr3.update()
        time.sleep(1)