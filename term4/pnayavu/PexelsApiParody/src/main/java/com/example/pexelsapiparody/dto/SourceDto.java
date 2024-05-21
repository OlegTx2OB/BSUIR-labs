package com.example.pexelsapiparody.dto;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class SourceDto {
    @JsonProperty("id") private long id;
    @JsonProperty("original_url") private String original;
    @JsonProperty("medium_url") private String medium;
}