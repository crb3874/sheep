#include "LaplacianYoungMaterial.h"

registerMooseObject("SheepApp", LaplacianYoungMaterial);

InputParameters
LaplacianYoungMaterial::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription("bleh");
  params.addRequiredCoupledVar("variable","coupled var");

  return params;

}

LaplacianYoungMaterial::LaplacianYoungMaterial(const InputParameters & parameters) : Material(parameters),
										     _k(declareADProperty<Real>("k")),
										     _grad_u(adCoupledGradient("variable"))
{
  
}

void
LaplacianYoungMaterial::computeQpProperties()
{
  _k[_qp] = 1 / std::sqrt(1 + _grad_u[_qp] * _grad_u[_qp]);
  _inverse_k[_qp] = std::sqrt(1+grad_u[_qp] * _grad_u[_qp]);
}

