    import { initializeApp } from "https://www.gstatic.com/firebasejs/9.14.0/firebase-app.js";
    import { getAnalytics } from "https://www.gstatic.com/firebasejs/9.14.0/firebase-analytics.js";

    const firebaseConfig = {
      apiKey: "AIzaSyAMNA_43DheedkFH2Q4ZTvXiGHT42d6cEg",
      authDomain: "tsa-pju-b204b.firebaseapp.com",
      databaseURL: "https://tsa-pju-b204b-default-rtdb.asia-southeast1.firebasedatabase.app",
      projectId: "tsa-pju-b204b",
      storageBucket: "tsa-pju-b204b.appspot.com",
      messagingSenderId: "1069280038428",
      appId: "1:1069280038428:web:f8549d6b550aa9a2f099d9",
      measurementId: "G-KHKBGMJ2TM"
    };

    // Initialize Firebase
    // const app = initializeApp(firebaseConfig);
    // const analytics = getAnalytics(app);

    // import {
    //     getDatabase,
    //     ref,
    //     set,
    //     child,
    //     get
    // }
    // from "https://www.gstatic.com/firebasejs/9.14.0/firebase-database.js";
    // const db = getDatabase();
    // const dbref = ref(db);

const app = initializeApp(firebaseConfig);
var database = firebase.database().ref("data");
database.on("value", function(snapshot) {
  var Status = snapshot.child("status").val();
  var currentSensor = snapshot.child("arus").val();
  var lightSensor = snapshot.child("ldr").val();
  var voltageSensor = snapshot.child("tegangan").val();
  var temperature = snapshot.child("suhu").val();

  $("#Status").text(Status);
  $("#currentSensor").text(currentSensor);
  $("#lightSensor").text(lightSensor);
  $("#voltageSensor").text(voltageSensor);
  $("#temperature").text(temperature);

});