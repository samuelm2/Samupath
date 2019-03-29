#include "pch.h"
#include "MultiJitteredSampler.h"
#include "glm/gtc/random.hpp"
#include <algorithm>
#include <iostream>

//Implementation inspired by Pixar https://graphics.pixar.com/library/MultiJitteredSampling/paper.pdf

void MultiJitteredSampler::generate_samples(int num_samples, int num_sets)
{
	this->num_samples = num_samples;
	this->num_sets = num_sets;
	int grid_dim = glm::floor(glm::sqrt((float)num_samples));
	for (int i = 0; i < num_sets; i++) {
		for (int j = 0; j < grid_dim; j++) {
			for (int k = 0; k < grid_dim; k++) {
				Point2D p = Point2D();
				p.x = (double)((k + 1) * grid_dim - 1 - j + glm::linearRand(0., 1.))/num_samples;
				p.y = (double)((j + 1) * grid_dim - 1 - k + glm::linearRand(0., 1.))/num_samples;

				samples.push_back(p);
			}
		}
	}
	shuffle_x();
	shuffle_y();
}

void MultiJitteredSampler::shuffle_x() {
	int grid_dim = glm::floor(glm::sqrt((float)num_samples));
	for (int i = 0; i < num_sets; i++) {
		for (int row = 0; row < grid_dim; row++) {
			int new_row = (int)((float)row + glm::linearRand(0., 1.) * (float)(grid_dim - row));
			for (int col = 0; col < grid_dim; col++) {
				if (num_samples*i + row * grid_dim + col > num_samples * num_sets || num_samples * i + new_row * grid_dim + col > num_samples * num_sets) {
					std::cout << "fuck" << std::endl;
				}
				std::swap(samples[num_samples*i + row * grid_dim + col].x, samples[num_samples*i + new_row * grid_dim + col].x);
			}
		}
	}
}

void MultiJitteredSampler::shuffle_y() {
	int grid_dim = glm::floor(glm::sqrt((float)num_samples));
	for (int i = 0; i < num_sets; i++) {
		for (int col = 0; col < grid_dim; col++) {
			int new_col = (int)((float)col + glm::linearRand(0., 1.) * (float)(grid_dim - col));
			for (int row = 0; row < grid_dim; row++) {
				if (num_samples*i + row * grid_dim + col > num_samples * num_sets || num_samples * i + row * grid_dim + new_col > num_samples * num_sets) {
					std::cout << "fuck" << std::endl;
				}
				std::swap(samples[num_samples*i + row * grid_dim + col].y, samples[num_samples*i + row * grid_dim + new_col].y);
			}
		}
	}
}



void MultiJitteredSampler::print_samples()
{
	for (int i = 0; i < samples.size(); i++) {
		Point2D p = samples[i];
		std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
	}
}

MultiJitteredSampler::MultiJitteredSampler()
{
}

