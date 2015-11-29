Feature: Location

  Scenario: A new location
    Given I have a new location
    When I get the country code
    And I get the region code
    And I get the postal code
    And I get the city
    And I get the street
    And I get the number
    Then country code should be ""
    And region code should be ""
    And postal code should be ""
    And city should be ""
    And street should be ""
    And number should be ""

  Scenario: Red Hat Amphitheater
    Given I have the Red Hat Amphitheater location
    When I get the country code
    And I get the region code
    And I get the postal code
    And I get the city
    And I get the street
    And I get the number
    Then country code should be "USA"
    And region code should be "NC"
    And postal code should be "27601"
    And city should be "Raleigh"
    And street should be "S McDowell St"
    And number should be "500"

  Scenario: Red Hat Headquarters
    Given I have the Red Hat Headquarters location
    When I get the country code
    And I get the region code
    And I get the postal code
    And I get the city
    And I get the street
    And I get the number
    Then country code should be "USA"
    And region code should be "NC"
    And postal code should be "27601"
    And city should be "Raleigh"
    And street should be "E Davie St"
    And number should be "100"
