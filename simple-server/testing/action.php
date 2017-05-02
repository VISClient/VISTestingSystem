<?php
	
	$code = $_POST['code'];
	$input = $_POST['input'];

	$src_file = fopen("file.cpp", "w");
	
	if ($src_file === FALSE) {
		print_r(error_get_last());
	}

	fwrite($src_file, $code);
	fclose($src_file);
	
	$input_file = fopen("input.txt", "w");
	
	if ($input_file === FALSE) {
		print_r(error_get_last());
	}

	fwrite($input_file, $input);
	fclose($input_file);		

	exec('g++ -std=c++11 file.cpp -o file');
	exec('./file < input.txt > output.txt');

	sleep(2);

	$output_file = fopen("output.txt", "r");	
	$output = fread($output_file, filesize("output.txt"));
	fclose($output_file);

	echo $output;

?>
