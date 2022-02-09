#include "application.h"
#include "utils.h"
#include "image.h"
#include <cmath>

//To make the user input
#include <iostream>
using namespace std;

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);

framebuffer.resize(w, h);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;

	foto1.loadTGA("../res/foto1.tga");
	toolbar.loadTGA("../res/toolbar.tga");
	build_matrix();

	initParticles();
	first_time = true;
	shape = 1;	
}

//render one frame
void Application::render(Image& framebuffer)
{	
	if (task == 0) {
		task0();
	}
	else if (task == 1) {
		task1();
	}
	else if (task == 2) {
		task2();
	}
	else if (task == 3) {
		task3();
	}
	else if (task == 4) {
		task4();
	}
	else if (task == 5) {
		task5();
	}
	else if (task == 6) {
		task6();
	}
}

void Application::task0() {
	//clear framebuffer if we want to start from scratch
	framebuffer.fill(Color::BLACK);

	//here you can add your code to fill the framebuffer

	//fill every pixel of the image with some random data
	for (unsigned int x = 0; x < framebuffer.width; x++)
	{
		for (unsigned int y = 0; y < framebuffer.height; y++)
		{
			framebuffer.setPixel(x, y, Color(randomValue() * 255, randomValue() * 255, randomValue() * 255)); //random color
		}
	}
}

void Application::task1() {

	framebuffer.fill(Color::BLACK);

	//Line

	//Chech the draw line if we want to write lines backwards:
	//framebuffer.drawLine(590, 50, 20, 50, Color(192, 192, 192));
	framebuffer.drawLine(20, 50, 590, 50, Color(192, 192, 192));
	framebuffer.drawLine(50, 80, 620, 80, Color(192, 192, 192));

	framebuffer.drawLine(20, 50, 50, 80, Color(192, 192, 192));
	framebuffer.drawLine(40, 50, 70, 80, Color(192, 192, 192));
	framebuffer.drawLine(590, 50, 620, 80, Color(192, 192, 192));
	framebuffer.drawLine(570, 50, 600, 80, Color(192, 192, 192));

	framebuffer.drawLine(165, 50, 195, 80, Color(192, 192, 192));
	framebuffer.drawLine(270, 50, 300, 80, Color(192, 192, 192));
	framebuffer.drawLine(380, 50, 410, 80, Color(192, 192, 192));
	framebuffer.drawLine(500, 50, 530, 80, Color(192, 192, 192));

	//H
	framebuffer.drawRectangle(50, 120, 30, 160, Color(255, 0, 0), true);
	framebuffer.drawRectangle(140, 120, 30, 160, Color(255, 0, 0), true);
	framebuffer.drawRectangle(80, 187, 60, 25, Color(255, 0, 0), false);

	//E
	framebuffer.drawRectangle(190, 120, 30, 160, Color(128, 0, 128), true);
	framebuffer.drawRectangle(220, 120, 60, 25, Color(128, 0, 128), false);
	framebuffer.drawRectangle(220, 187, 60, 25, Color(128, 0, 128), false);
	framebuffer.drawRectangle(220, 255, 60, 25, Color(128, 0, 128), false);

	//L
	framebuffer.drawRectangle(295, 120, 30, 160, Color(255, 165, 0), true);
	framebuffer.drawRectangle(325, 120, 60, 25, Color(255, 165, 0), false);

	//L
	framebuffer.drawRectangle(410, 120, 30, 160, Color(255, 255, 0), true);
	framebuffer.drawRectangle(440, 120, 60, 25, Color(255, 255, 0), false);

	//O
	framebuffer.drawCircle(590, 200, 80, Color(124, 252, 0), true);
	framebuffer.drawCircle(590, 200, 60, Color(0, 0, 0), true);

	//!
	framebuffer.drawCircle(720, 100, 15, Color(0, 176, 246), true);
}

void Application::task2() {

	if (shape == 1) {
		float rStart = 255.0;
		float rEnd = 147;
		float gStart = 0.0;
		float gEnd = 112;
		float bStart = 0.0;
		float bEnd = 219;

		float r = (rEnd - rStart) / framebuffer.width;
		float g = (gEnd - gStart) / framebuffer.width;
		float b = (bEnd - bStart) / framebuffer.width;

		for (unsigned int x = 0; x < framebuffer.width; x++)
		{
			rStart = rStart + r;
			gStart = gStart + g;
			bStart = bStart + b;

			for (unsigned int y = 0; y < framebuffer.height; y++)
			{
				framebuffer.setPixel(x, y, Color(rStart, gStart, bStart));
			}
		}
	}

	else if (shape == 2) {
		for (unsigned int x = 0; x < framebuffer.width; x++) {
			for (unsigned int y = 0; y < framebuffer.height; y++) {

				float xcoord = (float)((x - framebuffer.width / 2) * (x - framebuffer.width / 2));
				float ycoord = (float)((y - framebuffer.height / 2) * (y - framebuffer.height / 2));
				float updator = (float)(xcoord + ycoord) / (float)framebuffer.width;
				if (updator >= 255 || updator < 0)
					updator = 255;
				framebuffer.setPixel(x, y, Color(updator, updator, updator));
			}
		}
	}
}

void Application::task3() {

	if (shape == 1) {
		for (unsigned int x = 0; x < framebuffer.width; x++)
		{
			for (unsigned int y = 0; y < framebuffer.height; y++)
			{	
				framebuffer.setPixel(x, y, foto1.getPixel(x, y));
			}
		}
	}

	else if (shape == 2) {

		int r;
		int g;
		int b;

		for (unsigned int x = 0; x < framebuffer.width; x++)
		{
			for (unsigned int y = 0; y < framebuffer.height; y++)
			{
				r = 255 - foto1.getPixel(x, y).r;
				g = 255 - foto1.getPixel(x, y).g;
				b = 255 - foto1.getPixel(x, y).b;
				framebuffer.setPixel(x, y, Color(r, g, b));
			}
		}
	}

	else if (shape == 3) {

		int r;
		int g;
		int b;
		int avarage;

		for (unsigned int x = 0; x < framebuffer.width; x++)
		{
			for (unsigned int y = 0; y < framebuffer.height; y++)
			{
				r =  foto1.getPixel(x, y).r;
				g =  foto1.getPixel(x, y).g;
				b =  foto1.getPixel(x, y).b;
				avarage = (r + b + g) / 3;
				framebuffer.setPixel(x, y, Color(avarage, avarage, avarage));
			}
		}
	}
}

void Application::task4() {

	framebuffer.fill(Color::BLACK);

	for (unsigned int i = 0; i < framebuffer.height; i++) {
		for (unsigned int j = 0; j < framebuffer.width; j++) {
			framebuffer.setPixelSafe(i, j, matrixPixels[j][i]);
		}
	}
}

void::Application::build_matrix() {
	framebuffer.fill(Color::BLACK);

	matrixPixels = new Color * [framebuffer.width];
	for (unsigned int i = 0; i < framebuffer.width; i++) {
		matrixPixels[i] = new Color[framebuffer.height];
	}

	for (unsigned int i = 0; i < framebuffer.width; i++)
	{
		for (unsigned int j = 0; j < framebuffer.height; j++)
		{
			matrixPixels[i][j] = foto1.getPixelSafe(i, j);
		}
	}
}

void Application::task5() {
	renderParticles();
}

void Application::task6() {
	if (first_time == true) {
		CanvasMaker();
		first_time = false;
	}
	else {
		Drawer();
	}
}

//called after render
void Application::update(double seconds_elapsed)
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	if (keystate[SDL_SCANCODE_SPACE]) //if key space is pressed
	{
		//...
	}

	//to read mouse position use mouse_position
}

//keyboard press event 
void Application::onKeyDown( SDL_KeyboardEvent event )
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	switch(event.keysym.scancode)
	{	
		case SDL_SCANCODE_0:
			task = 0;
			break;
		case SDL_SCANCODE_1:
			task = 1;
			break;		
		case SDL_SCANCODE_2:
			task = 2;
			break;
		case SDL_SCANCODE_A:
			shape = 1;
			break;
		case SDL_SCANCODE_B:
			shape = 2;
			break;
		case SDL_SCANCODE_C:
			shape = 3;
			break;
		case SDL_SCANCODE_3:
			task = 3;
			break;
		case SDL_SCANCODE_4:
			task = 4;
			break;
		case SDL_SCANCODE_5:
			task = 5;
			break;
		case SDL_SCANCODE_6:
			task = 6;
			break;        

		case SDL_SCANCODE_D:
			BrushSize(true);
			break;
		case SDL_SCANCODE_I:
			BrushSize(false);
			break;

		case SDL_SCANCODE_ESCAPE:
			exit(0); 
			break; //ESC key, kill the app
	}
}

//keyboard key up event 
void Application::onKeyUp(SDL_KeyboardEvent event)
{
	//...
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse pressed
	{
		whileClick = true;//if you read mouse position from the event, careful, Y is reversed, use mouse_position instead
	}
}

void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
	{
		whileClick = false;
	}
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}

void Application::initParticles() {

	for (int i = 0; i < 50; i++) {
		particlesArray[i].x = rand() % (framebuffer.width - max_size) + 1;
		particlesArray[i].y = rand() % (framebuffer.height - max_size) + 1;
		particlesArray[i].size = rand() % (max_size) + 2;
	}
}

void Application::renderParticles() {

	for (int i = 0; i < 50; i++) {
		framebuffer.drawCircle(particlesArray[i].x, particlesArray[i].y, particlesArray[i].size, Color(0, 0, 0), true);
	}

	updateParticles();

	for (int i = 0; i < 50; i++) {
		framebuffer.drawCircle(particlesArray[i].x, particlesArray[i].y, particlesArray[i].size, Color(0, 176, 246), true);
	}
}

void Application::updateParticles() {
	if (time > 5) {
		time -= time;
	}

	for (int i = 0; i < 50; i++) {
		if (particlesArray[i].y - particlesArray[i].size >= particlesArray[i].size) {
			//particlesArray[i].y -= time * 1,5;	
			particlesArray[i].y -= 1;
		}
		else if (particlesArray[i].y - particlesArray[i].size <= particlesArray[i].size) {

			particlesArray[i].x = rand() % (framebuffer.width - 1) + 1;
			particlesArray[i].y =  rand() % (framebuffer.height - 1) + 1;
		}
	}
}

void Application::PaintThing() {

	if (mouse_position.y > 50 && mouse_position.y <= framebuffer.height &&
		mouse_position.x <= framebuffer.width) {
		for (int i = 0; i < SizeDrawer; i++) {
			for (int j = 0; j < SizeDrawer; j++) {
				framebuffer.setPixel(mouse_position.x + i, mouse_position.y + j, SelectedColor);
			}
		}
	}
	else {
		if (mouse_position.y > 10 && mouse_position.y < 40) {
			if (mouse_position.x > 10 && mouse_position.x < 36) {
				CanvasMaker(); //this creates the canvas again so its the same as clearing it (not sure if optimal because we are creating everything back again)
			}
			else if (mouse_position.x > 60 && mouse_position.x < 90) {
				//section to save image Sadge
			}
			else if (mouse_position.x > 110 && mouse_position.x < 140) {
				SelectedColor = Color::BLACK;

			}
			else if (mouse_position.x > 160 && mouse_position.x < 190) {
				SelectedColor = Color::RED;

			}
			else if (mouse_position.x > 210 && mouse_position.x < 240) {
				SelectedColor = Color::GREEN;

			}
			else if (mouse_position.x > 260 && mouse_position.x < 290) {
				SelectedColor = Color::BLUE;

			}
			else if (mouse_position.x > 310 && mouse_position.x < 340) {
				SelectedColor = Color::YELLOW;

			}
			else if (mouse_position.x > 360 && mouse_position.x < 390) {
				SelectedColor = Color::PURPLE;

			}
			else if (mouse_position.x > 410 && mouse_position.x < 440) {
				SelectedColor = Color::BLUE;

			}
			else if (mouse_position.x > 460 && mouse_position.x < 490) {
				SelectedColor = Color::WHITE;

			}
		}
	}
}

void Application::BrushSize(bool increase) {
	if (increase) {
		SizeDrawer = SizeDrawer - 3;
	}
	else {
		SizeDrawer = SizeDrawer + 3;
	}
}

void Application::CanvasMaker() {
	for (unsigned int i = 0; i < framebuffer.width; i++) {
		for (unsigned int j = 0; j < framebuffer.height; j++) {
			if (j < 50) {
				framebuffer.setPixelSafe(i, j, toolbar.getPixelSafe(i, j)); //we replace all 0-50 pixels with the toolbar.tga pixels
			}
			else {
				framebuffer.setPixelSafe(i, j, Color::WHITE);
			}
		}
	}
}

void Application::Drawer() {
	if (whileClick == true) {
		PaintThing();
	}
}