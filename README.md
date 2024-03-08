# CG
Project for Computer Graphics Class using OpenGL / Glut.


# Correr o projeto

Gerar a Makefile:
```sh
$ cmake .
```

Gerar os executáveis:
```sh
$ make
```

## Utilizar o generator

```sh
$ cd generator
```

### Gerar uma figura

```sh
$ ./generator <figura> <dados> <ficheiro de output> 
```
Nota: Todos os ficheiros gerados pelo **generator** serão criados na pasta `models`.

**Lista de figuras e inputs**:
1. `./generator plane <length> <divisions> <output>`
2. `./generator box <length> <divisions> <output>`
3. `./generator cone <radius> <height> <slices> <stacks> <output>`
4. `./generator cylinder <radius> <height> <slices> <output>`
5. `./generator sphere <radius> <slices> <stacks> <output>`
6. `./generator torus <majorRadius> <minorRadius> <sides> <rings> <output>`

## Utilizar o engine
```sh
$ cd engine
```

### Abrir uma cena (.xml)
```sh
$ ./engine <path>
```
Nota: Todas as cenas que utilizamos poderão se encontradas na pasta `scenes`.

### Abrir um modelo (.3d/.obj)
```sh
$ ./engine <path>
```
Nota: Todas os modelos que utilizamos poderão se encontradas na pasta `models`.