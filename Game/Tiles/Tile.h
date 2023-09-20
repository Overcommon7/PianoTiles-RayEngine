#pragma once
class Tile : public IObservable1<Selectable>, public IObservable1<GameObject>
{
public:
	static inline const Vector2 SIZE = { 100, 175 };

	Tile(Vector2 spawnPosition);
	inline RayEngine::Transform* Transform() { return button->Transform(); }
	inline const Collider* Collider() const { return button->GetCollider(); }
	void SetClicked();
private:
	Button* button;
	bool clicked;
	void OnInvoke(Selectable& arg1) override;
	void OnInvoke(GameObject& arg1) override;
};

