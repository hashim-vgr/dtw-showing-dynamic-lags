# DTW-Showing-Dynamic-Lags
DTW is a method to quantify the similarity between two time series or sequences exhibiting a certain likeness but may vary in speed and amplitude. 

DTW can be used to calculate the similarites between 2 times series.

But here i'm showing how to use it to calculate the dynamic lags between two time series signals.
 ## what are dynamic lags?
 
<img width="842" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/b3a56f5c-e114-4a4c-9148-af851cae5327">
<br>
Like the image shown above, dynamic lags give information on wether a current sample is leading of lagging correspoinding to it's counterpart in the other signal.

## detailed breadown of the process
### step 1: take 2 signals with same number of samples (s1.txt and s2.txt in the code provided)
<img width="432" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/9ca6e348-90da-45f0-b5ce-3ec96053f729">
<br>

### step 2: calculate error matrix with a defined search window (given as 100 in the code)
<img width="481" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/46ffd419-f076-4dc9-903b-7f0215745e23">
<br>
<img width="481" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/3c779546-38b8-4b57-ada7-31596e189fb6">
<br>

### step 3: accumulated the errors by an interval of H (value set as 50 in the code)
<img width="465" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/5eddf71f-ea42-4189-9569-dfc02279401c">
<br>
<img width="468" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/647ba077-2101-4609-a88a-9df0e7e52d57">
<br>

### step 4: backtrack through the accumulated indices to get dynamic lags
<img width="468" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/dc639c55-14f2-4b15-9753-258b45a90255">
<br>
the red arrow shows the way we backtrack
<br>

### step 5: interpolate the lag waveform to the same number as our number of samples
<img width="467" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/b815efca-3040-4993-93bf-013657d7e92d">
<br>
this wave form means:
1. For positive values of lag waveform, signal 1 is leading in respect to signal 2
2. For negative values of lag waveform, signal 1 is lagging in respect to signal 2

Happy coding...!!!


