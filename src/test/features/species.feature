Feature: Species

  Scenario: A new species
    Given I have a new species
    When I get the species name
    Then the species name should be ""

  Scenario: A Lupus species
    Given I have the Lupus species
    When I get the species name
    Then the species name should be "Lupus"
