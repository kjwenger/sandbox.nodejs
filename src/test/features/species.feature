Feature: Species

  @non-ignore
  Scenario: A new species
    Given I have a new genus
    And I have a new species
    When I get the genus name
    And I get the species name
#    And I read the genus "name" property
#    And I read the species "name" property
    Then the genus name should be ""
    And the species name should be ""
#    And the genus "name" property should be ""
#    And the species "name" property should be ""

  Scenario: A Lupus species
    Given I have the "Canis" genus
    And I have the "Lupus" species
    When I get the genus name
    And I get the species name
#    And I read the genus "name" property
#    And I read the species "name" property
    Then the genus name should be "Canis"
    And the species name should be "Lupus"
#    And the genus "name" property should be "Canis"
#    And the species "name" property should be "Lupus"

  Scenario: A Lupus species
    Given I have the "Canis" genus
    And I have the "Lupus" species
    When I set the genus name to "Wolfs- und Schakalartige"
    And I set the species name to "Wolf"
    And I get the genus name
    And I get the species name
#    And I read the genus "name" property
#    And I read the species "name" property
    Then the genus name should be "Wolfs- und Schakalartige"
    And the species name should be "Wolf"
#    And the genus "name" property should be "Wolfs- und Schakalartige"
#    And the species "name" property should be "Wolf"
