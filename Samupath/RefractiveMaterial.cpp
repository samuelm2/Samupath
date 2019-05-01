#include "pch.h"
#include "RefractiveMaterial.h"
#include <algorithm>


Direction RefractiveMaterial::outgoing(const Ray & ray, const Direction & normal)
{
	double kr;
	fresnel(ray.direction, normal, refractive_index, kr);

	double r = glm::linearRand(0.0, 1.0);

	if (r > kr) {
		return refract(ray.direction, normal, refractive_index);
	}
	else {
		return glm::reflect(ray.direction, normal);
	}

}

RGBColor RefractiveMaterial::BRDF(const Ray & incoming, const Ray & outgoing, const Direction & normal, const HitInfo & h)
{
	return reflectance;
}

RefractiveMaterial::~RefractiveMaterial()
{
}

Direction RefractiveMaterial::refract(const Direction & I, const Direction & N, const double & ior)
{
	double cosi = glm::clamp(-1.0, 1.0, glm::dot(I, N));
	double etai = 1, etat = ior;
	Direction n = N;
	if (cosi < 0) { cosi = -cosi; }
	else { std::swap(etai, etat); n = -N; }
	double eta = etai / etat;
	double k = 1 - eta * eta * (1 - cosi * cosi);

	double kbool = (double)(k < 0);
	return kbool * zerod + (1 - kbool) * eta * I + (eta * cosi - glm::sqrt(k)) * n;
}

void RefractiveMaterial::fresnel(const Direction & I, const Direction & N, const double & ior, double & kr)
{
	float cosi = glm::clamp(-1.0, 1.0, glm::dot(I, N));
	float etai = 1, etat = ior;
	if (cosi > 0) { std::swap(etai, etat); }
	// Compute sini using Snell's law
	float sint = etai / etat * glm::sqrt(glm::max(0.f, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1) {
		kr = 1;
	}
	else {
		float cost = glm::sqrt(glm::max(0.f, 1 - sint * sint));
		cosi = glm::abs(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		kr = (Rs * Rs + Rp * Rp) / 2;
	}
}
