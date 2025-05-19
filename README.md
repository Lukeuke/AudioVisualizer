# AudioVisualizer

### Automatic build

#### Windows:
``build-windows.ps1``

#### Linux:
```shell
chmod +x build_and_run.sh
./build_and_run.sh
```

### Build manual

**1st time**
```shell
cmake -B build && cmake --build build
```
**2nd time and onwards**
```
cmake --build build
```
Output inside:

```shell
cd /build/bin/Debug
```