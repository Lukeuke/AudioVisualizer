# AudioVisualizer
Audio visualizer made in C++

## Automatic build

#### Windows:
```shell
.\build-windows.ps1
```

#### Linux:
```shell
chmod +x build-liunx.sh
./build-liunx.sh
```

### Build manual

**1st time (or when adding new libraries)**
```shell
cmake -B build
cmake --build build
```
**2nd time and onwards**
```
cmake --build build
```
Output inside:

```shell
cd /build/bin/Debug
```

## Contributing
Check out the [CONTRIBUTING.md](CONTRIBUTING.md) file for guidelines.
