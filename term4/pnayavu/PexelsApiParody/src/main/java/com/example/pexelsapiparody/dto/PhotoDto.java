package com.example.pexelsapiparody.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
public class PhotoDto {
    private long id;
    private String photographer;
    private SourceDto sourceDto;
}
