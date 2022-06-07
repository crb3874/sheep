//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "LaplacianDiffusion.h"

registerMooseObject("SheepApp", LaplacianDiffusion);

InputParameters
LaplacianDiffusion::validParams()
{
  auto params = ADKernelGrad::validParams();
  params.addClassDescription("Same as `Diffusion` in terms of physics/residual, but the Jacobian "
                             "is computed using forward automatic differentiation");
  return params;
}

LaplacianDiffusion::LaplacianDiffusion(const InputParameters & parameters) : ADKernelGrad(parameters) {}

ADRealVectorValue
LaplacianDiffusion::precomputeQpResidual()
{
  ADReal k = 1/std::sqrt(1+_grad_u[_qp]*_grad_u[_qp]);
  return k * _grad_u[_qp];
}
