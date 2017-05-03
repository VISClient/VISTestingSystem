angular.module('app', [])
 
.controller('taskCtrl', function($scope, $scope){
  /*
   * Создаем список элементов
   */
  $scope.itemsList = [
    {'name': 'A'},
    {'name': 'B' },
    {'name': 'C'},
    {'name': 'D'},
  ];


})

.controller('langCtrl', function($scope, $scope){
  /*
   * Создаем список элементов
   */

   $scope.itemsList2 = [
    {'name': 'C++ 14 '},
    {'name': 'C++ 11' },
    {'name': 'Java 8.0'},
    {'name': 'Java 6.0'},
    {'name': 'Pascal '},
    {'name': 'Phyton '},
    {'name': 'OCaml '}
  ];
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










