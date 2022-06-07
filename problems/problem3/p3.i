sigma = 0.2
  
[Mesh]
  [cmg]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 1
    ymax = 1
    nx = 20
    ny = 20
  []
[]

[Variables]
  [u]
  []
[]

[Kernels]
  [lap_young_diffusion]
    type = ADMatDiffusion
    variable = u
    diffusivity = k
  []
  [rx]
    type = Reaction
    variable = u
    rate = 1.0
  []
[]

[Materials]
  [lymat]
    type = LaplacianYoungMaterial
    variable = u
  []
[]
  
[BCs]
  [neumann]
    type = ADMatNeumannBC
    variable = u
    value = ${sigma}
    boundary = 'top bottom left right'
    boundary_material = inverse_k
  []
[]
 
[Executioner]
  type = Steady
  solve_type = 'NEWTON'
  petsc_options_iname = '-pc_type'
  petsc_options_value = 'hypre'
[]
  
[Outputs]
  exodus = true
[]
