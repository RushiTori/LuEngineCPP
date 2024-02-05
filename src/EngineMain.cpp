#include "EngineMain.hpp"

void LuEngineSetup(const std::vector<std::string>& args, uint32_t width, uint32_t height, const std::string& projName,
				   uint32_t targetFPS, ConfigFlags flags) {
	for (uint i = 1; i < args.size(); i++) {
		if ((args[i] == "--help") || (args[i] == "-h")) {
			std::cout << "This is the helper message for \"" << ProjectTitle << "\"." << std::endl;
			std::cout << "\nList of common app args (dashes required):" << std::endl;
			std::cout << "  -h OR --help : prints this helper message" << std::endl;
			std::cout << "  -f OR --fullscreen : sets the app resolution to fullscreen" << std::endl;
			std::cout << "  -r OR --resolution {width} {height} : sets the app resolution" << std::endl;
			std::cout << "\nList of this app's args (dashes required):" << std::endl;
			std::cout << "  No specific args for this app." << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	ProjectTitle = projName;

	bool doFullScreen = false;
	for (uint i = 1; i < args.size(); i++) {
		if ((args[i] == "--fullscreen") || (args[i] == "-f")) doFullScreen = true;
		if ((args[i] == "--resolution") || (args[i] == "-r")) {
			if (i + 2 >= args.size()) {
				printf("missing args after \"%s\"\nshould be : %s {width} {height}\n", args[i].c_str(),
					   args[i].c_str());
				exit(EXIT_FAILURE);
			} else {
				width = std::stoi(args[++i]);
				height = std::stoi(args[++i]);
			}
		}
	}

	SetConfigFlags(flags);
	InitWindow(width, height, projName.c_str());
	if (doFullScreen) {
		SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
		ToggleFullscreen();
	}
	SetTargetFPS(targetFPS);
	SetWindowFocused();

	Assets::LoadAssets();
	InputHandler::Reset();
	globalCamera = WorldCamera(GetScreenSizes() / 2, 1);

	std::cout << std::endl;
	std::cout << "Project : " << ProjectTitle << std::endl;
	std::cout << std::endl;
}

void LuEngineUpdate() {
	frameCount++;
	InputHandler::Update();

	SetWindowTitle((ProjectTitle + " - " + std::to_string(GetFPS()) + " fps").c_str());
}

void LuEngineDestroy() {
	Assets::UnloadAssets();
	CloseWindow();
}
