# DTW-Showing-Dynamic-Lags
## About the Project
This is done as part of the Blood Pulse Cycle Cutting project during an academic research internship under the Healthcare Technology Innovation Center (HTIC) at IIT Madras. The team members include Hashim P, Ayisha Jumaila TP, and Ajisha T, under the guidance of Dr. Nabeel PM (Lead Research Scientist, HTIC IITM) and Mr. Raj Kiran V (Project Scientist). We thank them for their guidance and support.

DTW (Dynamic Time Warping) is a method to quantify the similarity between two time series or sequences exhibiting a certain likeness but may vary in speed and amplitude. DTW can be used to calculate the similarities between two time series.

But here We're showing how to use it to calculate the dynamic lags between two time series signals.


 ## What are Dynamic lags?
 
<img width="842" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/b3a56f5c-e114-4a4c-9148-af851cae5327">
<br>
Like the image shown above, dynamic lags give information on wether a current sample is leading of lagging correspoinding to it's counterpart in the other signal.

## Detailed Breadown of the Process
### step 1: Take 2 signals with same number of samples (s1.txt and s2.txt in the code provided)
<img width="432" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/9ca6e348-90da-45f0-b5ce-3ec96053f729">
<br>

### step 2: Calculate error matrix with a defined search window (given as 100 in the code)
<img width="481" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/46ffd419-f076-4dc9-903b-7f0215745e23">
<br>
<img width="481" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/3c779546-38b8-4b57-ada7-31596e189fb6">
<br>

### step 3: Accumulated the errors by an interval of H (value set as 50 in the code)
<img width="465" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/5eddf71f-ea42-4189-9569-dfc02279401c">
<br>
<img width="468" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/647ba077-2101-4609-a88a-9df0e7e52d57">
<br>

### step 4: Backtrack through the accumulated indices to get dynamic lags
<img width="468" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/dc639c55-14f2-4b15-9753-258b45a90255">
<br>
The red arrow shows the way we backtrack
<br>

### step 5: Interpolate the lag waveform to the same number as our number of samples
<img width="467" alt="image" src="https://github.com/hashim-vgr/dtw-showing-dynamic-lags/assets/90979621/b815efca-3040-4993-93bf-013657d7e92d">
<br>
This wave form means:
1. For positive values of lag waveform, signal 1 is leading in respect to signal 2
2. For negative values of lag waveform, signal 1 is lagging in respect to signal 2

Happy coding...!!!


