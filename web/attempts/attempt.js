 angular.module('attemptApp', []) // version to load from server
 // .controller('ResultCtrl', function ($scope, $http){
 //    $http.get('results.json').success(function(data) {
 //      $scope.countries = data;
 //    });
 //  });

   .controller('AttemptCtrl', function ($scope){ // testing version
    $scope.atts = [
      {"time": "10", "task": "A", "attempt": "1", "result": "WA 17"},
      {"time": "30", "task": "A", "attempt": "2", "result": "OK"},
      {"time": "20", "task": "B", "attempt": "1", "result": "OK"}
      
    ];
});


