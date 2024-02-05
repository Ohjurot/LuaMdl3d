info("Generating demo cube materials")
demo_materials()

local A_size = 2
local B_size = 1

info("Generating a demo cube A")
object("A")
cursor_set(A_size, A_size, A_size)
demo_cube(A_size)

info("Generating a demo cube B")
object("B")
cursor_set(A_size * 2 + 1 + B_size, B_size, A_size * 2 + 1 + B_size)
demo_cube(B_size)

save("demo")
