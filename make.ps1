# Remove-Item -Recurse -Force Builds

cmake -B Builds -G "Visual Studio 17 2022"
cmake --build Builds --config Release -j5

$exePath = "C:\Users\felix\Downloads\testplugin\test\Builds\test_artefacts\Release\Standalone\test.exe"

if ($LASTEXITCODE -eq 0) {
    # Run the executable if it exists
    if (Test-Path $exePath) {
        Write-Host "Running $exePath..."
        & $exePath
    } else {
        Write-Host "Error: Executable not found at $exePath"
    }
}
else {
    Write-Host "Error: Build failed."
}
