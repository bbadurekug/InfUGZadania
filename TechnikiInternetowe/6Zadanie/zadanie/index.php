<?php

	class Dowcip{
		
		public string $tytul;
		public string $zawartosc;
		
		public function __construct(string $tytul, string $zawartosc){
			
			$this->tytul = $tytul;
			$this->zawartosc = $zawartosc;
			
		}
		
	}
	
	$dowcipy = [];
						
	$dowcipy_file=fopen('dowcipy.txt','r');
	
	while(!feof($dowcipy_file)){
		
		$linia = '';
		$tytul = '';
		$zawartosc = '';
		
		$tytul = fgets($dowcipy_file);
		
		while(($linia = fgets($dowcipy_file)) !== false && $linia != ''){
			
			if(trim($linia) === ''){
			
				break;
			
			}
			
			$zawartosc .= $linia;

		}					
		
		$dowcipy[] = new Dowcip($tytul, $zawartosc);
		
	}
	
	fclose($dowcipy_file);	

?>

<!DOCTYPE html>
<html lang="pl-PL">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <title>Strona z dowcipami</title>
    <link
      rel="stylesheet"
      href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0/css/all.min.css"
    >
	
	<link rel="stylesheet" href="css/style.css">
    <!-- Google Fonts Roboto -->
    <link
      rel="stylesheet"
      href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;500;700;900&display=swap"
    >
    <!-- MDB -->
    <link rel="stylesheet" href="css/mdb.min.css">
	
	<script
		src="https://cdnjs.cloudflare.com/ajax/libs/mdb-ui-kit/6.4.0/mdb.min.js"
	></script>
	
	<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"></script>
	
  </head>
  <body>

    <!-- Start your project here-->
	<header>
	
		<div class="container-fluid d-flex align-items-center justify-content-center bg-primary text-white md-5 py-3">
	
			<h1>Strona z dowcipami informatycznymi</h1>
	
		</div>
	
	</header>

<!--Main layout-->
<main>
	
	<div class="continer bg-secondary text-white py-3 mb-5">
	
		<h4 class="d-flex align-items-center justify-content-center">Wybierz metodę wyświetlania dowcipów!</h4>
		
		<div class="d-flex align-items-center justify-content-center w-100">
		
			<input type="radio" class="btn-check" name="options" id="option1" checked>
			<label class="btn btn-secondary flex-fill mx-2 text-center" for="option1">Karty</label>
			
			<input type="radio" class="btn-check" name="options" id="option2">
			<label class="btn btn-secondary flex-fill mx-2 text-center" for="option2">Akordeon</label>
			
			<input type="radio" class="btn-check" name="options" id="option3">
			<label class="btn btn-secondary flex-fill mx-2 text-center" for="option3">Karuzela</label>
		
		</div>
		
	</div>

  <div class="container">

    <section id="karty" class="mb-5">

    <div class="row justify-content-center"> 

		<?php foreach ($dowcipy as $dowcip): ?>

		<div class="col-lg-4 col-md-6 mb-4 d-flex justify-content-center"> 

			<div class="card text-bg-primary mb-3 d-flex text-center" style="width: 20rem;">
			
				<div class="card-header">
				
					<h5><?= htmlspecialchars($dowcip->tytul) ?></h5>
				
				</div>
            
				<div class="card-body">
					
					<pre class="card-text"><?= htmlspecialchars($dowcip->zawartosc) ?></pre>
				
				</div>
          
		  </div>

        </div>

		<?php endforeach; ?>

	</div>

	</section>
    <!-- Section: Pricing -->
	
	<div id="akordeon">
	
		<?php foreach ($dowcipy as $index => $dowcip): ?>
			<?php $collapseID = 'collapse' . $index; ?>
			
			<div class="mb-5">
			
			<p class="d-flex justify-content-center">
				<a
					class="btn btn-primary mb-3"
					data-bs-toggle="collapse"
					href="#<?= $collapseID ?>"
					role="button"
					aria-expanded="false"
					aria-controls="<?= $collapseID ?>"
				>
					<?= htmlspecialchars($dowcip->tytul) ?>
				</a>
			</p>

			<div class="collapse" id="<?= $collapseID ?>">
				<div class="d-flex justify-content-center text-center">
					<pre class="card-text d-inline-block"><?= htmlspecialchars($dowcip->zawartosc) ?></pre>
				</div>
			</div>
			
			</div>
			
		<?php endforeach; ?>
	
	</div>
	
	<section id="karuzela">
	
	<div id="demo" class="carousel slide mb-5 mb-primary" data-bs-ride="carousel">

  <!-- Indicators/dots -->
		  <div class="carousel-indicators md-5">
			
			<?php foreach ($dowcipy as $index => $dowcip): ?>
			 
				<button type="button" data-bs-target="#demo" data-bs-slide-to="<?= $index ?>" class="<?= $index === 0 ? 'active' : ''?>"></button>
				
			<?php endforeach; ?>
		
		  </div>
		  
		  <!-- The slideshow/carousel -->
		  
			<div class="carousel-inner d-flex align-items-center text-center bg-primary text-white ">
			  
				<?php foreach ($dowcipy as $index => $dowcip): ?>
			 
					<div class="carousel-item <?= $index === 0 ? 'active' : ''?>">
						<h5><?= htmlspecialchars($dowcip->tytul) ?></h5>
						<pre class="card-text"><?= htmlspecialchars($dowcip->zawartosc) ?></pre>
					</div>
				
				<?php endforeach; ?>
				
			</div>
		  
		  <!-- Left and right controls/icons -->
		  <button class="carousel-control-prev" type="button" data-bs-target="#demo" data-bs-slide="prev">
			<span><i class="fas fa-chevron-left" style="color: white; font-size: 24px;"></i></span>
		  </button>
		  <button class="carousel-control-next" type="button" data-bs-target="#demo" data-bs-slide="next">
			<span><i class="fas fa-chevron-right" style="color: white; font-size: 24px;"></i></span>
		  </button>
		</div>
	
	</section>

  </div>
  
</main>

<footer>

	<div class="container-fluid bg-secondary text-white py-3 md-5">
	
		<h5 class="d-flex align-items-center justify-content-center">Źródła</h5>
		
		<ul class="list-group list-group-flush d-flex align-items-center justify-content-center">
		
			<li class="list-group-item"><a href="https://bulldogjob.pl/readme/suchary-programisty">Suchary programisty</a></li>
			<li class="list-group-item"><a href="https://forum.pasja-informatyki.pl/6231/kawaly-o-programistach-informatykach-d">Pasja informatyki</a></li>
			<li class="list-group-item"><a href="https://www.dowcipy.pl/k/informatyka/">Dowcipy.pl</a></li>
			
		</ul>
	
	</div>

</footer>
<!--Main layout-->


    <!-- End your project here-->

    <!-- MDB -->
	
	<script>
		document.querySelectorAll('[data-mdb-collapse-init]').forEach(el => {
			new mdb.Collapse(el);
		});
	</script>
	
    <script src="js/radio.js"></script>
   
  </body>
</html>