mox_project("luamdl3d_ui")
mox_cpp("C++20")
mox_windowed()

links { 
    "luamdl3d_lib", 
}

dependson { 
    "luamdl3d", 
}
