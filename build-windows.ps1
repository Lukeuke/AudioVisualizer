$buildExists = Test-Path -Path "./build" -PathType Container
$debugBuildExists = Test-Path -Path "./cmake-build-debug" -PathType Container

if (-not ($buildExists -or $debugBuildExists)) {
    cmake -B build
    cmake --build build
} else {
    cmake --build build
}

$exePath = "./build/bin/Debug/AudioVisualizer.exe"
if (Test-Path -Path $exePath) {
    & $exePath
} else {
    Write-Host "Executable not found: $exePath"
}