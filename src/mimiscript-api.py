class PyObj(TinyObj):
    def importClass(className: str, fp: FILE):
        pass

    def newObj(objName: str, className: str, fp: FILE):
        pass


class Test (BaseObj):
    def test(val1: str, val2: int) -> float:
        pass


class Root (SysObj):
    test = Test()

    def reboot():
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

    def getPtr(id: int) -> MimiObj:
        pass


class LED (TinyObj):
    def on(id: int, io: int, name: str):
        pass

    def off():
        pass

    def setId(id: int):
        pass
