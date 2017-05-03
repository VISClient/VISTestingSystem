angular.module('app', [])
 

 .controller('SubmitCntr', function ($scope, $http){ // testing version
        $scope.submit = function (file) {
            $http.post("http://happyest.ru/getdata?type=0", file).success(function(data) {
                $scope.mas = data.a
                console.log("OK")
            }).error(function (data) {
              console.log("OOOPS")
                //console.log(data)
            })
        }
  }) 
       
.controller('taskCtrl', function($scope, $scope, $http, $log, $window){

var selectedFile;

$scope.file_changed = function(element) {

     $scope.$apply(function(scope) {
         selectedFile = element.files[0];
         var reader = new FileReader();
         reader.onload = function(e) {
            // handle onload
         };
         reader.readAsDataURL(selectedFile);
     });
   }


  $scope.problemList = ['A', 'B', 'C', 'D']
  $scope.languageList = ['C++ 14', 'Java', 'OCaml', 'Idris']

  $scope.submitClick = function () {
    console.log($scope.problem)
    console.log($scope.languages)
    console.log(selectedFile)

    $http.post("http://github.com/api/send?problem=" + $scope.problem + "&language=" + $scope.languages, {'file': photofile}).success(
     //$http.get("http://github.com").success(
        function (data) {
         $window.location.href = '../attempts/attempts.html'
        }
      ).error(
        function (data) {
          console.log("OOOP")
           
        }
      )
  }       
  $scope.selectProblem = function(id) {
    $log.info(id)
  }

  var test = function () {
    $log.info("preload function")
  }

  test()





})






 
/*
 * Объявляем директиву, которая будет создавать сам список
 */
.directive('dropdownList',function( $timeout ){
  return {
    restrict: 'E',
    scope: {
      itemsList: '=',
      placeholder: '@'
    },
    template: '<input type="text" ng-model="search" placeholder="{{ placeholder }}" />' +
        '<div class="search-item-list"><ul class="list">' +
        '<li ng-repeat="item in itemsList | filter:search" ng-click="chooseItem( item )">{{ item.name }}' +
          '<span class="amount">{{ item.amount }}</span>' +
         '</li>' +
        '</ul></div>',
    link: function(scope, el, attr){
        var $listContainer = angular.element( el[0].querySelectorAll('.search-item-list')[0] );
        el.find('input').bind('focus',function(){
          $listContainer.addClass('show');
        });
        el.find('input').bind('blur',function(){
          /*
             * 'blur' реагирует быстрее чем ng-click,
             * поэтому без $timeout chooseItem не успеет поймать item до того, как лист исчезнет
             */
          $timeout(function(){ $listContainer.removeClass('show') }, 200);
        });
      
        scope.chooseItem = function( item ){
         scope.search = item.name;
           $listContainer.removeClass('show');
       }
    }
  }
});










