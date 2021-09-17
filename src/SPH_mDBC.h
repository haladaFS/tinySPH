#pragma once

#include "SPH_defs.h"
#include "SPH_particle_system.h"

#include "SPH_kernel_approx.h"

//mDBC density aproximation for boundary particle
void mDBC_compute_density
(Particle_system &particles, Simulation_data simulation_data, real y_w)
{

	realvec r;
	realvec gn;
	realvec gnd;

	#pragma omp parallel for schedule(static)
	for(int p = 0; p < particles.np; p++)
	{

		if(particles.data.part_type[p] == wall)
		{

			r = particles.data.r[p];
			gn.x = r.x;
			gn.y = y_w + fabs(r.y - y_w);
			//gnd = r - gn;
			gnd = gn - r;

			//particles.data.rho[p] = Kernel_density_approximation_mDBC(particles, simulation_data, gn);
			particles.data.rho[p] = Kernel_density_approximation_MATRIX_mDBC(particles, simulation_data, gn, gnd);

		} // if function - check part type

	} // cycle over particles

}


//mDBC density aproximation for boundary particle
void mDBC_compute_density_mdbcGeo
(Particle_system &particles, Simulation_data simulation_data)
{


	#pragma omp parallel for schedule(static)
	for(int p = 0; p < particles.np; p++)
	{

		if(particles.data.part_type[p] == wall)
		{

			realvec r;
			realvec gn;
			realvec gnd;

			r = particles.data.r[p];
			gn = particles.special.gnr[p];

			//gnd = r - gn;
			gnd = gn - r;

			//particles.data.rho[p] = Kernel_density_approximation_mDBC(particles, simulation_data, gn);
			particles.data.rho[p] = Kernel_density_approximation_MATRIX_mDBC(particles, simulation_data, gn, gnd);

		} // if function - check part type

	} // cycle over particles

}

void mDBC_compute_density_bt
(Particle_system &particles, Simulation_data simulation_data, real y_w)
{

	realvec r;
	realvec gn;
	realvec gnd;

	#pragma omp parallel for schedule(static)
	for(int p = 0; p < particles.np; p++)
	{

		if(particles.data.part_type[p] == wall)
		{

			r = particles.data.r[p];
			gn.x = r.x;
			gn.y = y_w + fabs(r.y - y_w);
			//gnd = r - gn;
			gnd = gn - r;

			//particles.data.rho[p] = Kernel_density_approximation_mDBC(particles, simulation_data, gn);
			particles.data.rho[p] = Kernel_density_approximation_MATRIX_mDBC(particles, simulation_data, gn, gnd);
			//particles.data.rho[p] = Kernel_density_approximation(particles, simulation_data, r);

			if (particles.data.rho[p] > 1500 || particles.data.rho[p] < 0)
			{std::cout << "[Computde mDBC_BT] rho = " << particles.data.rho[p] << std::endl; }

		} // if function - check part type

	} // cycle over particles

}