

https://github.com/user-attachments/assets/b9fadeea-6ad6-4876-a817-d007b71eb1ce


# Features

- Four synchronized gauges updating at 60fps from a single time base
- Quadratic acceleration, RPM-correlated fuel consumption, thermal inertia engine warmup
- Proportional layout  
- Reusable gauge component 
- Qt 5.15.2 compatible ( portable to Qt 6)

## Build


# Prerequisites: Qt 5.15.2 (MinGW 64-bit)
$env:Path += ";<Qt_PATH>/5.15.2/mingw81_64/bin;<Qt_PATH>/Tools/mingw810_64/bin"

mkdir build && cd build
qmake ..\ivi-vehicle-dashboard.pro
mingw32-make -j4
.\release\ivi-vehicle-dashboard.exe
