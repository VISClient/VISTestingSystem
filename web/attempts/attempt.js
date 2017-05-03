 




 angular.module('app', []) // version to load from server
 // .controller('AttemptCtrl', function ($scope, $http){
 //    $http.get('attempts.json').success(function(data) {
 //      $scope.atts = [
 //      {"time": "10", "task": "A", "attempt": "1", "result": "WA 17"},
 //      {"time": "30", "task": "A", "attempt": "2", "result": "OK"},
 //      {"time": "20", "task": "B", "attempt": "1", "result": "OK"}]
 //    }).error(function (data) {
 //    	$scope.atts = [
 //      	{"time": "10", "task": "A", "attempt": "1", "result": "WA 17"},
 //      	{"time": "30", "task": "A", "attempt": "2", "result": "OK"},
 //      	{"time": "20", "task": "B", "attempt": "1", "result": "OK"}]
 //      })
 //  });

   .controller('AttemptCtrl', function ($scope){ // testing version
    $scope.atts = [
      {"time": "10", "task": "A", "attempt": "1", "result": "WA 17"},
      {"time": "30", "task": "A", "attempt": "2", "result": "OK"},
      {"time": "20", "task": "B", "attempt": "1", "result": "OK"}
    
    ];
});


