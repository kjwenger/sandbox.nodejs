Feature: Topic

  Scenario: A new topic
    Given I have a new topic
    When I get the topic name
    Then the topic name should be ""

  Scenario: A USA topic
    Given I have the USA topic
    When I get the topic name
    Then the topic name should be "USA"
