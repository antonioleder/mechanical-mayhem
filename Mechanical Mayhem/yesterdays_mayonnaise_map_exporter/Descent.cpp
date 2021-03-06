// Level: Descent.
// Map data automatically generated by Processing.
// Each pair of floats in an array is a coordinate for a tile, in tilemap space.

float staticSpikes[44] = {
	1.0f, 47.0f, 2.0f, 47.0f, 3.0f, 47.0f, 4.0f, 47.0f, 5.0f, 47.0f, 6.0f, 47.0f, 7.0f, 47.0f, 8.0f, 47.0f, 9.0f, 47.0f, 10.0f, 47.0f, 11.0f, 47.0f, 12.0f, 47.0f, 13.0f, 47.0f, 14.0f, 47.0f, 15.0f, 47.0f, 16.0f, 47.0f, 
	17.0f, 47.0f, 18.0f, 47.0f, 19.0f, 47.0f, 20.0f, 47.0f, 21.0f, 47.0f, 22.0f, 47.0f
};

for (int i = 0; i < 44; i += 2)
{
	GameObject* spike = new GameObject(*objectManager.GetArchetypeByName("StaticSpike"));
	static_cast<Transform*>(spike->GetComponent("Transform"))->SetTranslation(Vector2D(staticSpikes[i] * 100.0f, staticSpikes[i + 1] * -100.0f));
	objectManager.AddObject(*spike);
}

float chipsSpawns[18] = {
	17.0f, 7.0f, 21.0f, 10.0f, 6.0f, 12.0f, 5.0f, 21.0f, 18.0f, 21.0f, 13.0f, 27.0f, 14.0f, 32.0f, 9.0f, 43.0f, 20.0f, 43.0f
};

for (int i = 0; i < 18; i += 2)
{
	GameObject* chips = new GameObject(*objectManager.GetArchetypeByName("Collectible"));
	static_cast<Transform*>(chips->GetComponent("Transform"))->SetTranslation(Vector2D(chipsSpawns[i] * 100.0f, chipsSpawns[i + 1] * -100.0f));
	objectManager.AddObject(*chips);
}

float powerups[12] = {
	19.0f, 14.0f, 3.0f, 16.0f, 20.0f, 30.0f, 2.0f, 32.0f, 18.0f, 38.0f, 5.0f, 42.0f
};

for (int i = 0; i < 12; i += 2)
{
	GameObject* powerup = new GameObject(*objectManager.GetArchetypeByName("Powerup"));
	static_cast<Transform*>(powerup->GetComponent("Transform"))->SetTranslation(Vector2D(powerups[i] * 100.0f, powerups[i + 1] * -100.0f));
	objectManager.AddObject(*powerup);
}

