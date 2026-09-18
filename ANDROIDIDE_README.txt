KALPIT OpenMind AI - AndroidIDE ready shell

1. Extract this folder.
2. Open the folder in AndroidIDE (select the folder containing settings.gradle).
3. Let Gradle sync.
4. Build > Assemble Debug APK.
5. Install the APK.

The app currently loads http://127.0.0.1:3000.
That address is intentional: it is where the OpenMind Node server should run on the same phone (for example in Termux).

If you use a remote server instead, edit MainActivity.java:
OPENMIND_URL = "https://YOUR-SERVER-DOMAIN";
Then rebuild.
