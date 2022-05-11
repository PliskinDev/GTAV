#pragma once

typedef void* Void;
typedef int Any;
typedef unsigned int uint;
typedef int Hash;
typedef int BOOL;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;

typedef struct {
	float x, y, z;
} Vector3;

typedef struct {
	unsigned char r, g, b, a;
} Color;

typedef union RGBA
{
	struct
	{
		union { int red; int r; };
		union { int green; int g; };
		union { int blue; int b; };
		union { int opacity; int alpha; int a; };
	};
	int col[4];
} RGBA;
typedef int rgba;