#pragma once

#include <main.h>
#include <array>
#include <algorithm>
#include "boundingbox.h"
#include <iostream>
#include <cmath>

using namespace glm;


class Node
{
public:
	static void InitializePreLink(GLuint program);
	static void InitializePostLink(GLuint program);

	Node();
	void SetTransform(const mat4 &transform);
	void AddChild(Node *child);
	Node* GetParent();
protected:
	glm::mat4 fullTransform();

	mat4 _transform;
	std::vector<Node*> _children;
	Node* _parent;

	static GLint uniform_model, uniform_color;
	static GLint attribute_position, attribute_normal;
};

class Shape : public Node
{
public:
	Shape();
	virtual void Render();
	void SetAABoundingBox(std::array<vec3,2> &coordsToBeSet, std::array<vec3, 2> &coords);
	void SetBoundingBox(std::array<vec3, 8> &coordsToBeSet, std::array<vec3, 8> &coords);
	void ApplyTransformation();
	std::array<vec3,2> GetBoundingBox() const;
	std::array<vec3, 2> aabbox_coords;
	std::array<vec3, 8> init_bbox_coords;
	std::array<vec3, 8> bbox_coords;
	
	virtual ~Shape();
protected:
	GLuint _vertexBuffer, _indexBuffer, _vao, _vao2;
	vec3 _color;
};

class Box : public Shape
{
public:
	Box(vec3 size, vec3 color);
	virtual void Render() override;
	void setInitialTransformation(mat4 &mat);

protected:
	std::array<VertexPositionNormal, 36> vertices;
	vec3 _size;
};	

class Cylinder : public Shape
{
public:
	static const int slices;
	Cylinder(double radius, double height, vec3 color);
	virtual void Render() override;
protected:
	double _radius, _height;
	std::array<VertexPositionNormal, 1440> vertices;
};

class Sphere : public Shape
{
public:
	Sphere(double radius, vec3 color);
	virtual void Render() override;
	void Init(const mat4 &mat = mat4());
protected:
	double _radius, _height;
};

class Collisions{
public:
	//Detection par axis aligned bounding boxes
	static bool AABBDetection(const Shape  &shape1, const Shape &shape2);
	//Detection par oriented bounding boxes, algorithme SAT (Separating Axis Theorem)
	static bool OBBDetection(const Shape& shape1, const Shape& shape2);
};
