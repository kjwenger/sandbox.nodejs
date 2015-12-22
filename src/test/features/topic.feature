Feature: Topic

  Scenario: A new topic
    Given I have a new topic
    When I get the name
    Then name should be ""

  Scenario: A USA topic
    Given I have the USA topic
    When I get the name
    Then name should be "USA"
