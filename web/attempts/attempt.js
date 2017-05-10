 




 angular.module('app', []) // version to load from server
 // .controller('AttemptCtrl', function ($scope, $http){
 //    $http.get('attempts.json').success(function(data) {
 //      $scope.atts = data
 //  	}
 //  });

   .controller('AttemptCtrl', function ($scope){ // testing version
    $scope.atts = [
      {"task": "A", "attempt": "1", "result": "WA 17"},
      {"task": "A", "attempt": "2", "result": "OK"},
      {"task": "B", "attempt": "1", "result": "OK"}
    
    ];
});


