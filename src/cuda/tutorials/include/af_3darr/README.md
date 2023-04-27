+ 3D Calculations 
    - 2D Block, 3D Grid
        - `tx + Bx*ty + Bx*By*bx + Bx*By*Gx*by + Bx*By*Gx*Gy*bz`
        - index direction:
            1. Thread in x axis of the block
            2. Thread in y axis of the block
            3. Block in x axis of the grid
            4. Block in y axis of the grid
            5. Block in z axis of the grid
    - 3D Block, 3D Grid
        - `tx + Bx*ty + Bx*By*tz + Bx*By*Bz*bx + Bx*By*Bz*Gx*by + Bx*By*Bz*Gx*Gy*bz`
        - index direction:
            1. Thread in x axis of the block
            2. Thread in y axis of the block
            3. Thread in z axis of the block
            4. Block in x axis of the grid
            5. Block in y axis of the grid
            6. Block in z axis of the grid