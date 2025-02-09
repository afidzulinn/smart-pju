
<!DOCTYPE html>
<?php
    require("conn.php");

     $sql = mysqli_query ($conn,"SELECT * FROM  `datapju` ORDER BY id DESC");  
    if (!$sql) 
        {
            die ('Invalid query: '.mysqli_error($conn));
        }  
?>
<html lang="en">
        <?php if(mysqli_num_rows($sql)>0){ ?>
        <?php
            while($data = mysqli_fetch_array($sql)){
            $status  = $data["status"];
            $suhu = $data["suhu"];
            $arus = $data["arus"];

            }   
        }
        ?>
<head>
  <meta charset="utf-8">
  <meta content="width=device-width, initial-scale=1.0" name="viewport">

  <title>Dashboard - Smart PJU</title>
  <meta content="" name="description">
  <meta content="" name="keywords">

  <!-- Favicons -->
  <link href="assets/img/lampu.png" rel="icon">
  <link href="assets/img/lampu.png" rel="apple-touch-icon">

  <!-- Google Fonts -->
  <link href="https://fonts.gstatic.com" rel="preconnect">
  <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,400i,600,600i,700,700i|Nunito:300,300i,400,400i,600,600i,700,700i|Poppins:300,300i,400,400i,500,500i,600,600i,700,700i" rel="stylesheet">

  <!-- Vendor CSS Files -->
  <link href="assets/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
  <link href="assets/vendor/bootstrap-icons/bootstrap-icons.css" rel="stylesheet">
  <link href="assets/vendor/boxicons/css/boxicons.min.css" rel="stylesheet">
  <link href="assets/vendor/quill/quill.snow.css" rel="stylesheet">
  <link href="assets/vendor/quill/quill.bubble.css" rel="stylesheet">
  <link href="assets/vendor/remixicon/remixicon.css" rel="stylesheet">
  <link href="assets/vendor/simple-datatables/style.css" rel="stylesheet">

  <!-- Template Main CSS File -->
  <link href="assets/css/style.css" rel="stylesheet">
</head>

<body>

  <!-- ======= Header ======= -->
  <header id="header" class="header fixed-top d-flex align-items-center">

    <div class="d-flex align-items-center justify-content-between">
      <a href="index.html" class="logo d-flex align-items-center">
        <img src="assets/img/lampu.png" alt="">
        <span class="d-none d-lg-block">Smart PJU</span>
      </a>
      <i class="bi bi-list toggle-sidebar-btn"></i>
    </div><!-- End Logo -->
  </header><!-- End Header -->

  <!-- ======= Sidebar ======= -->
  <aside id="sidebar" class="sidebar">

    <ul class="sidebar-nav" id="sidebar-nav">

      <li class="nav-item">
        <a class="nav-link " href="dashboard.html">
          <i class="bi bi-grid"></i>
          <span>Dashboard</span>
        </a>
      </li><!-- End Dashboard Nav -->
        
      <li class="nav-item">
        <a class="nav-link " href="data.html">
          <i class="bi bi-grid"></i>
          <span>Data</span>
        </a>
      </li><!-- End Dashboard Nav -->

      <li class="nav-item">
        <a class="nav-link " href="index.html">
          <i class="bi bi-grid"></i>
          <span>Home</span>
        </a>
      </li><!-- End Dashboard Nav -->

    </ul>
  </aside><!-- End Sidebar-->

  <main id="main" class="main">

    <div class="pagetitle">
      <h1>Dashboard</h1>
      <nav>
        <ol class="breadcrumb">
          <li class="breadcrumb-item"><a href="index.html">Home</a></li>
          <li class="breadcrumb-item active">Dashboard</li>
        </ol>
      </nav>
    </div><!-- End Page Title -->

    <section class="section dashboard">
      <div class="row">

        <!-- Left side columns -->
        <div class="col-lg-12">
          <div class="row">

            <!-- Status Card -->

            <div class="col-xxl-4 col-md-6">
              <div class="card info-card sales-card">

                <div class="card-body">
                  <h5 class="card-title">Status </h5>

                  <div class="d-flex align-items-center">
                    <div class="card-icon rounded-circle d-flex align-items-center justify-content-center">
                      <i class="bi bi-lightbulb"></i>
                    </div>
                    <div class="ps-3">
                      <h6 class="text-center" id="Status"><?php echo $status;?></h6>
                      
                    </div>
                  </div>
                </div>

              </div>
            </div><!-- End Status Card -->

            <!-- Cahaya Card -->
            <div class="col-xxl-4 col-md-6">
              <div class="card info-card sales-card">

                <div class="card-body">
                  <h5 class="card-title">Sensor Cahaya </h5>

                  <div class="d-flex align-items-center">
                    <div class="card-icon rounded-circle d-flex align-items-center justify-content-center">
                      <i class="bi bi-brightness-high"></i>
                    </div>
                    <div class="ps-3">
                      <h6 class="text-center" id="lightSensor"><?php echo $;?></h6>

                    </div>
                  </div>
                </div>

              </div>
            </div><!-- End Cahaya Card -->

            <!-- Temperature Card -->
            <div class="col-xxl-4 col-md-6">
              <div class="card info-card temperature-card">

                <div class="card-body">
                  <h5 class="card-title">Temperature </h5>

                  <div class="d-flex align-items-center">
                    <div class="card-icon rounded-circle d-flex align-items-center justify-content-center">
                      <i class="bi bi-thermometer-half"></i>
                    </div>
                    <div class="ps-3">
                      <h6 class="text-center" id="temperature"><?php echo $suhu;?> &#8451;</h6>

                    </div>
                  </div>
                </div>

              </div>
            </div><!-- End Temperature Card -->

            <div class="col-xxl-4 col-md-6">
              <div class="card info-card revenue-card">

                <div class="card-body">
                  <h5 class="card-title">Tegangan </h5>

                  <div class="d-flex align-items-center">
                    <div class="card-icon rounded-circle d-flex align-items-center justify-content-center">
                      <i class="bi bi-lightning"></i>
                    </div>
                    <div class="ps-3">
                      <h6 class="text-center" id="voltageSensor"> Volt</h6>

                    </div>
                  </div>
                </div>

              </div>
            </div><!-- End Tegangan Card -->

            <!-- Arus Card -->
            <div class="col-xxl-4 col-md-6">

              <div class="card info-card arus-card">

                <div class="card-body">
                  <h5 class="card-title">Arus</h5>

                  <div class="d-flex align-items-center">
                    <div class="card-icon rounded-circle d-flex align-items-center justify-content-center">
                      <i class="bi bi-lightning-charge"></i>
                    </div>
                    <div class="ps-3">
                      <h6 class="text-center" id="currentSensor"></h6>

                    </div>
                  </div>

                </div>
              </div>

            </div><!-- End Arus Card -->

          </div>
        </div><!-- End Left side columns -->
      </div>
    </section>
       <div class="col-lg-6 col-sm-12">
                                                <div class="mapouter">
                                                  <div class="gmap_canvas">
                                                    <iframe width="100%" height="200px" id="gmap_canvas" src="https://maps.google.com/maps?q=pens&t=&z=15&ie=UTF8&iwloc=&output=embed" frameborder="0" scrolling="no" marginheight="0" marginwidth="0"></iframe>
                                                      <a href="https://fmovies-online.net">fmovies</a><br>
                                                        <style>.mapouter{position:relative;text-align:right;height:200px;}</style>
                                                      <a href="https://www.embedgooglemap.net">custom embedded google map</a>
                                                        <style>.gmap_canvas {overflow:hidden;background:none!important;height:200px;}</style>
                                                  </div>
                                                </div>
                                              </div>

  </main><!-- End #main -->

  <a href="#" class="back-to-top d-flex align-items-center justify-content-center"><i class="bi bi-arrow-up-short"></i></a>

  <!-- Vendor JS Files -->
  <script src="assets/vendor/apexcharts/apexcharts.min.js"></script>
  <script src="assets/vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="assets/vendor/chart.js/chart.min.js"></script>
  <script src="assets/vendor/echarts/echarts.min.js"></script>
  <script src="assets/vendor/quill/quill.min.js"></script>
  <script src="assets/vendor/simple-datatables/simple-datatables.js"></script>
  <script src="assets/vendor/tinymce/tinymce.min.js"></script>
  <script src="assets/vendor/php-email-form/validate.js"></script>

  <script src="assets/js/main.js"></script>
  <script src="assets/js/jquery/jquery.min.js"></script>
  
  <!-- Firebase App -->
  <script src="assets/js/app.js"></script>

  <script src="https://www.gstatic.com/firebasejs/7.19.1/firebase-app.js"></script>
  <script src="https://www.gstatic.com/firebasejs/7.19.1/firebase-database.js"></script>

</body>

</html>