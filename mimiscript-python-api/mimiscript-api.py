class Test (BaseObj):
    def test(val1: str, val2: int) -> float:
        pass


class Test2 (Test):
    def test(val1: float, val2: int):
        pass


class Test1 (Test):
    def test():
        pass

    def test2():
        pass

    def getInfo() -> int:
        pass
