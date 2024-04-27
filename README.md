# CG
Project for Computer Graphics Class using OpenGL / Glut.

## Compilar o projeto

```sh
$ ./scripts/build.sh
```

## Correr o _engine_:

```sh
$ ./cg-engine <path>
```

Para correr o projeto com o vsync desativado (em máquina Linux):
```sh
$ export vblank_mode=0 && ./cg-engine <path>
```

## Correr o _generator_:

```sh
$ ./cg-generator <model> [args] <path>
```
| Model| args|
|:---|:---|
|`plane`| `<length> <divisions>`|
|`box`|`<length> <divisions>`|
|`cylinder`|`<radius> <height> <slices>`|
|`cone`|`<radius> <height> <slices> <stacks>`|
|`sphere`|`<radius> <slices> <stacks>`|
|`torus`|`<innerRadius> <outerRadius> <slices> <stacks>`|
|`patch`| `<bezier_patch> <tesselation>`| 



# Fases do Projeto

### 1ª Fase
- [Commit](https://github.com/JulioJPinto/CG-Project/tree/68b48d8db92162917e5cf2f37ba2e90da1f4d138)
- [Report](https://github.com/JulioJPinto/CG-Project/blob/68b48d8db92162917e5cf2f37ba2e90da1f4d138/Relat%C3%B3rio%20CG%20-%20Fase%201.pdf)

### 2ª Fase
- [Commit](https://github.com/JulioJPinto/CG-Project/tree/a9d251c0a458038bd26efecb48b57872c04f35f2)
- [Report](https://github.com/JulioJPinto/CG-Project/blob/a9d251c0a458038bd26efecb48b57872c04f35f2/Relat%C3%B3rio%20CG%20-%20Fase%202.pdf)

### 3ª Fase
- Commit
- [Report](https://github.com/JulioJPinto/CG-Project/blob/main/Relat%C3%B3rio%20CG%20-%20Fase%203.pdf)

### 4ª Fase
- Commit
- Report

