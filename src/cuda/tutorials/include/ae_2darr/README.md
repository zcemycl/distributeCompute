||B1x|B2x|
|---|---|---|
|B1y|T0T1<br>T2T3|T4T5<br>T6T7|
|B2y|T8T9<br>T10T11|T12T13<br>T14T15|

+ Other parameters
    - blockDim = (2,2,1), namely `(Bx, By, Bz)`
    - gridDim = (2,2,1), namely `(Gx, Gy, Gz)`
    - Thread idx `(tx, ty, tz)`
    - Block idx `(bx, by, bz)`
+ Calculations
    - top left : `tx + Bx*ty`
        ||B1x|
        |---|---|
        |B1y|T0T1<br>T2T3|
        - `0+2*0=0`, `1+2*1=1`, `0+2*1=2`, `1+2*1=3`

    - top right : `tx + Bx*ty + Bx*By*bx`
        ||B2x|
        |---|---|
        |B1y|T4T5<br>T6T7|
        - `0+2*0+2*2*1=4`
        - `1+2*0+2*2*1=5`
        - `0+2*1+2*2*1=6`
        - `1+2*1+2*2*1=7`
    - bottom : `tx + Bx*ty + Bx*By*bx + Bx*By*Gx*by`
        ||B1x|B2x|
        |---|---|---|
        |B2y|T8T9<br>T10T11|T12T13<br>T14T15|
        - `0+2*0+2*2*0+2*2*2*1=8`
        - `1+2*0+2*2*0+2*2*2*1=9`
        - `0+2*1+2*2*0+2*2*2*1=10`
        - `1+2*1+2*2*0+2*2*2*1=11`
        - `0+2*0+2*2*1+2*2*2*1=12`
        - `1+2*0+2*2*1+2*2*2*1=13`
        - `0+2*1+2*2*1+2*2*2*1=14`
        - `1+2*1+2*2*1+2*2*2*1=15`

+ 3D Calculations
    - `tx + Bx*ty + Bx*By*bx + Bx*By*Gx*by + Bx*By*Gx*Gy*bz`