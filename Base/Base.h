#pragma once

namespace RayEngine
{
	class Base
	{
	public:

		struct Data
		{
			Data(fs::path path) : rootDirectory(path) {}

			fs::path rootDirectory;
			int screenHeight = 720;
			int screenWidth = 1280;
			int targetFPS = -1;
			bool debugDraw = false;
			string title = "Default";
			Color clearColor = WHITE;
		};

		void Run(
			const Data& data,
			const vector<function<void()>>& initializers,
			const vector<function<void()>>& update,
			const vector<function<void()>>& draw,
			const vector<function<void()>>& shutdown);

		static Base* Get();

		inline void SetScreenWidth(int width) { data->screenWidth; SetWindowSize(data->screenWidth, data->screenHeight); }
		inline void SetScreenHeight(int height) { data->screenWidth; SetWindowSize(data->screenWidth, data->screenHeight); }
		inline void SetTitle(const string& title) { data->title = title; SetWindowTitle(title.c_str()); }
		inline void SetClearColor(Color color) { data->clearColor = color; }
		inline Vector2 GetScreenDimensions() const { return Vector2(data->screenWidth, data->screenHeight ); }

		constexpr const Data& GetData() const { return *data; }

	private:

		Data* data = nullptr;
		Font* drawFont = nullptr;

		void Initialize(const vector<function<void()>>& initializers);
		void Update(const vector<function<void()>>& update, const vector<function<void()>>& draw);
		void Shutdown(const vector<function<void()>>& shutdown);

		Base() = default;
		Base(Base& b) = delete;
		Base(Base&& b) = delete;
		Base& operator=(Base& b) = delete;
		Base& operator=(Base&& b) = delete;
	};
}

