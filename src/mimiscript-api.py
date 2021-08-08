class PyObj(SysObj):

    def importClass(className: str, fp: FILE):
        pass

    def newObj(objName: str, className: str, fp: FILE):
        pass

    def makeInlcude(fp: FILE):
        pass

    def makeNewObj(fp: FILE):
        pass


class PyClass (SysObj):
    def setSuper(superClassName: str):
        pass

    def makeApi(path: str):
        pass

    def makeHead(path: str):
        pass


class PyMethod (SysObj):
    def makeMethodFun(fp: FILE):
        pass

    def makeMethodDeclear(fp: FILE):
        pass

    def makeMethodDefine(fp: FILE):
        pass


class Compiler(SysObj):
    PyMethod()
    PyClass()
    PyObj()

    def build(pythonApiPath: str, outputPath: str):
        pass

    def analizeFile(pythonApiPath: str):
        pass


