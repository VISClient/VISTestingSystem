 angular.module('resultApp', []) // version to load from server
 // .controller('ResultCtrl', function ($scope, $http){
 //    $http.get('results.json').success(function(data) {
 //      $scope.countries = data;
 //    });
 //  });

   .controller('ResultCtrl', function ($scope){ // testing version
    $scope.results = [
      {"pos": "1", "name": "Соня", "a": "+", "b": "+", "c": ".", "d" : "+", "e" : "+", "f" : "+", "score" : "5", "time" : "200"},
      {"pos": "2", "name": "Baня", "a": "+", "b": "+2", "c": ".", "d" : "+", "e" : "+", "f" : "+18", "score" : "5", "time" : "500"},
      {"pos": "3", "name": "Вадя", "a": "-11", "b": "+", "c": ".", "d" : "-", "e" : "+", "f" : "-100", "score" : "4", "time" : "800"}
    ];
});


