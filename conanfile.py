from conan import ConanFile

class LuaMdl3dRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "PremakeDeps"

    def requirements(self):
        self.requires("spdlog/1.13.0")
        self.requires("argparse/3.0")
        self.requires("sol2/3.3.1")

    def configure(self):
        # This only works on windows (we added this so that you can see
        # how to change settings of packages)
        # self.options["spdlog"].wchar_support = True
        pass

