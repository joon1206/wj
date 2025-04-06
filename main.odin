package main

import "core:fmt"
import gl "vendor:OpenGL"
import sdl2 "vendor:sdl2"

main :: proc() {
	if (sdl2.Init(sdl2.INIT_VIDEO) < 0) {
		fmt.println("SDL Error: %s\n", sdl2.GetError())
	}
	defer sdl2.Quit()

	window := sdl2.CreateWindow(
		"3D Plate Packing",
		sdl2.WINDOWPOS_CENTERED,
		sdl2.WINDOWPOS_CENTERED,
		800,
		600,
		sdl2.WINDOW_OPENGL | sdl2.WINDOW_RESIZABLE,
	)
	if window == nil {
		fmt.eprintln("Failed to create window")
		return
	}
	defer sdl2.DestroyWindow(window)

	gl_context := sdl2.GL_CreateContext(window)
	defer sdl2.GL_DeleteContext(gl_context)
	sdl2.GL_MakeCurrent(window, gl_context)
	gl.load_up_to(3, 3, sdl2.gl_set_proc_address)

	mainLoop: for {

		event: sdl2.Event
		for sdl2.PollEvent(&event) != false {
			#partial switch event.type {
			case .QUIT:
				break mainLoop
			}
		}
		gl.ClearColor(0.2, 0.3, 0.3, 1.0)
		gl.Clear(gl.COLOR_BUFFER_BIT)

		sdl2.GL_SwapWindow(window)
	}
}
