<strong>HBuzzer Trigger</strong> or HBT(هبط) for shorts, is a mini project that I designed for my mother to call me from upstairs with ease LOL, the project consists of two parts:
<ul>
  <li>
    <strong>Mobile App:</strong>
  the mobile app is built using React Native(EXPO), it's a simple app with single button that send the post request to the IOT(esp32) local server to execute the action of beeping.

  <br>
  <img width="100" src="https://github.com/user-attachments/assets/bea91356-ee82-45e2-8776-e850ce822d5d">
  <br>
  <ol>
    	<li>
		<strong>State 1: Waiting for user to execute</strong><br>
		<img width="200" src="https://github.com/user-attachments/assets/190263d3-0546-423a-a4d8-72a72c2f3d13">
	</li>
	<li>
		<strong>State 2: Request sent successfully to esp32, app disabling button for 20s for the esp32 to end beeping and return to state 1
		</strong><br>
		<img width="200" src="https://github.com/user-attachments/assets/f2e66314-fa6c-46eb-bf7d-37fc6df88759">
	</li>
	<li>
		<strong>State 3: Request failed to reach esp32(offline or wifi problem)</strong><br>
		<img width="200" src="https://github.com/user-attachments/assets/2f9b233a-def4-4ad3-9a60-5d8b7dbc84e3">
	</li>
  </ol>

  </li>
  <li>
    <strong>IOT system:</strong>
    <p>the IOT system consists of an esp32 linked to a buzzer component, the esp32 act as a server with static ip (192.168.1.100) on local network that receives POST requests from the app on it's end point /trigger, the esp32 then reponds with a status code of 200 signaling the success and initiating a repeated beeping sound for 20s.</p>
    <br>
    <img width="200" src="https://github.com/user-attachments/assets/3b530359-cefd-485e-a0ea-b15d05cbcf88">
  </li>

</ul>

<p>Within this project u will find the code for both the app and the esp32 to easily replicate it on your own. have fun :)</p>
