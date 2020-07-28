# Uncomment below to enable build script debugging
#Set-PSDebug -Trace 1

$builddir = $args[0];

$vcpkgdist = 'master.zip';
$vcpkgdir = "$builddir\vcpkg";

$programfiles = ${Env:ProgramFiles(x86)}
$vswherepath = "$programfiles\Microsoft Visual Studio\installer\vswhere.exe"

$errormessage1 = "Microsoft Visual Studio Installer not found." 
$errormessage2 = "Microsoft C++ Build environment not found."
$errormessage3 = "Please install Microsoft Visual Studio with C++ SDK or Microsoft C++ Build Tools with English language pack from https://visualstudio.microsoft.com/visual-cpp-build-tools/"
$errormessage4 = "Failed to generate falltergeist.sln. Check the required vcpkg packages and cmake configuration."
$errormessage5 = "Failed to generate falltergeist.exe. Check for compile errors."

if (-Not(Test-Path "$vswherepath" -PathType leaf)) {
  throw "$errormessage1 $errormessage3"
}

$vsvarspath = &"$vswherepath" -products * -latest -requires Microsoft.Component.MSBuild -find **\Build\vcvars64.bat

#Write-Host "$vsvarspath"

if (-Not($vsvarspath -clike '*vcvars64.bat')) {
 throw "$errormessage2 $errormessage3"
}

# saving visual studio environment variables to temp file
cmd.exe /c "call `"$vsvarspath`" && set > %temp%\vcvars.txt"

# settings visual studio environment variables from temp file
Get-Content "$env:temp\vcvars.txt" | Foreach-Object {
   if ($_ -match "^(.*?)=(.*)$") {
      Set-Content "env:\$($matches[1])" $matches[2]
   }
}

if (Test-Path "$builddir\vcpkg-master\vcpkg.exe" -PathType leaf) {
 Write-Host "vcpkg tool found"
} else {
 Write-Host "Preparing vcpkg build..."

  if (Test-Path "$builddir/master.zip" -PathType leaf)  {
    Write-Host "Found vcpkg sources"
 
  } else {
    Write-Host "Downloading vcpkg sources..."
    Invoke-WebRequest -Uri "https://github.com/microsoft/vcpkg/archive/$vcpkgdist" -OutFile "$builddir\$vcpkgdist"
  }

  if ( -Not (Test-Path "$builddir\vcpkg-master\bootstrap-vcpkg.bat" -PathType leaf))  {
    Write-Host "Extracting vcpkg sources...";
    $shell = New-Object -COM Shell.Application; 
    $target = $shell.NameSpace($builddir); 
    $zipfile = "$builddir\master.zip";
    $zip = $shell.NameSpace($zipfile); 
    $target.CopyHere($zip.Items(), 1556);
  }

  Write-Host "Running vcpkg bootstrap..."

  &"$builddir\vcpkg-master\bootstrap-vcpkg.bat" -disableMetrics

  if (-Not(Test-Path "$builddir\vcpkg-master\vcpkg.exe" -PathType leaf)) {
    throw "Failed to build vcpkg"
  }
 
}

Write-Host "Installing dependencies..."
&"$builddir\vcpkg-master\vcpkg.exe" install sdl2:x64-windows sdl2-image:x64-windows sdl2-mixer:x64-windows zlib:x64-windows glew:x64-windows glm:x64-windows

Write-Host "Generating falltergeist.sln..."
&"cmake" -G"Visual Studio 16 2019" -A x64 -DCMAKE_TOOLCHAIN_FILE="$builddir/vcpkg-master/scripts/buildsystems/vcpkg.cmake" -B $builddir -S ..

if (-Not(Test-Path "$builddir/falltergeist.sln" -PathType leaf)) {
  throw "$errormessage4"
}

Write-Host "Building falltergeist..."

# Fixme: DEBUG config linked to wrong SDL dll, use RELEASE for now
&"cmake" --build $builddir --config RelWithDebInfo

if (-Not(Test-Path "$builddir/RelWithDebInfo/falltergeist.exe" -PathType leaf)) {
  throw $errormessage5
}
