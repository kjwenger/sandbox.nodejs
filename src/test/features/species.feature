Feature: Species

  Scenario: A new species
    Given I have a new genus
    And I have a new species
    When I get the genus name
    And I get the species name
    Then the genus name should be ""
    And the species name should be ""

  Scenario: A Lupus species
    Given I have the "Canis" genus
    And I have the "Lupus" species
    When I get the genus name
    And I get the species name
    Then the species name should be "Lupus"

  Scenario: A Lupus species
    Given I have the "Canis" genus
    And I have the "Lupus" species
    When I set the genus name to "Wolfs- und Schakalartige"
    And I set the species name to "Wolf"
    And I get the genus name
    And I get the species name
    Then the genus name should be "Wolfs- und Schakalartige"
    And the species name should be "Wolf"
