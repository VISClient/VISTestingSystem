angular.module('resultApp', []) 
    .controller('LoginCtrl', function ($scope, $http){ // testing version
        $scope.signin = function () {
            console.log('press login')
            console.log($scope.my_login)
            console.log($scope.my_password)
        }
        $scope.mas = [123,456,897]
        $scope.login = function () {
            $http.get("http://happyest.ru/getdata?type=0").success(function(data) {
                $scope.mas = data.a
                console.log(data)
            }).error(function (data) {
                console.log(data)
            }) 
        }
});