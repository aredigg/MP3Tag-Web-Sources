# iTunes API 2.2
# © 2021-2025 All Rights Reserved
[Name]=iTunes
[BasedOn]=https://itunes.apple.com/
[WordSeparator]=+
[Encoding]=url-utf-8
[IndexFormat]=%_url%|%_preview%|%_coverurl%|%Title%|%Artist%|%Tracks%|%Kind%|%Explicit%|%Released%|%Genre%|%Copyright%|%Notes%
[Settings]=&iTunes API#Settings….settings

[ParserScriptIndex]=...

json "on"

# debug "on" "debug-index.txt"

json_foreach "results"
    json_select "wrapperType"
    If "collection"
        json_select "collectionType"
        If "Album"
            json_select "collectionId"
            SayNextNumber
            Say "|"
            json_select "collectionViewUrl"
            Replace "?uo=4" ""
            Replace "&uo=4" ""
            SayRest
            Say "|"
            json_select "artworkUrl100"
            SayRest
            Say "|"
            json_select "collectionName"
            If ""
                json_select "collectionCensoredName"
            EndIf
            OutputTo "TEMP"
            SayRegexp "\s-\sSingle"
            IfOutput "TEMP"
                Set "KIND" "Single"
                Set "TEMP"
            EndIf
            SayRegexp "\s-\sEP"
            IfOutput "TEMP"
                Set "KIND" "EP"
                Set "TEMP"
            EndIf
            OutputTo "Output"
            Replace " - Single" ""
            Replace " - EP" ""
            RegexpReplace "\[.*\]" ""
            RegexpReplace "\{.*\}" ""
            SayRest
            Say "|"
            json_select "artistName"
            SayRest
            Say "|"
            json_select "trackCount"
            SayNextNumber
            Say "|"
            json_select "collectionType"
            IfOutput "KIND"
                SayOutput "KIND"
                Set "KIND"
            Else
                SayRest
            EndIf
            Say "|"
            json_select "collectionExplicitness"
            Replace "notExplicit" "No"
            Replace "explicit" "Yes"
            Replace "cleaned" "Cleaned"
            SayRest
            Say "|"
            json_select "releaseDate"
            SayNChars 10
            Say "|"
            json_select "primaryGenreName"
            SayRest
            Say "|"
            json_select "copyright"
            SayRest
            Say "|"
            json_select "collectionName"
            SayRegexp "(?<=\()[^)]*(?=\))"
            Say " "
            SayRegexp "(?<=\[)[^)]*(?=\])"
            Say " "
            SayRegexp "(?<=\{)[^}]*(?=\})"
            SayNewline
        EndIf
    EndIf
    IfVar "includeTracks" "true"
        If "track"
            json_select "kind"
            If "song"
                json_select "collectionId"
                SayNextNumber
                Say "|"
                json_select "collectionViewUrl"
                Replace "?uo=4" ""
                Replace "&uo=4" ""
                SayRest
                Say "|"
                json_select "artworkUrl100"
                SayRest
                Say "|"
                json_select "trackName"
                If ""
                    json_select "trackCensoredName"
                EndIf
                SayRest
                Say " ("
                json_select "collectionName"
                If ""
                    json_select "collectionCensoredName"
                EndIf
                OutputTo "TEMP"
                SayRegexp "\s-\sSingle"
                IfOutput "TEMP"
                    Set "KIND" "Track (Single)"
                    Set "TEMP"
                EndIf
                SayRegexp "\s-\sEP"
                IfOutput "TEMP"
                    Set "KIND" "Track (EP)"
                    Set "TEMP"
                EndIf
                OutputTo "Output"
                Replace " - Single" ""
                Replace " - EP" ""
                RegexpReplace "\[.*\]" ""
                RegexpReplace "\{.*\}" ""
                SayRest
                Say ")|"
                json_select "artistName"
                SayRest
                Say "|"
                json_select "trackCount"
                SayNextNumber
                Say "|"
                json_select "collectionType"
                IfOutput "KIND"
                    SayOutput "KIND"
                    Set "KIND"
                Else
                    Say "Track "
                    SayRest
                EndIf
                Say "|"
                json_select "trackExplicitness"
                Replace "notExplicit" "No"
                Replace "explicit" "Yes"
                Replace "cleaned" "Cleaned"
                SayRest
                Say "|"
                json_select "releaseDate"
                SayNChars 10
                Say "|"
                json_select "primaryGenreName"
                SayRest
                Say "|"
                json_select "copyright"
                SayRest
                Say "|"
                json_select "collectionName"
                SayRegexp "(?<=\()[^)]*(?=\))"
                Say " "
                SayRegexp "(?<=\[)[^)]*(?=\])"
                Say " "
                SayRegexp "(?<=\{)[^}]*(?=\})"
                SayNewline
            EndIf
            If "music-video"
                json_select "trackId"
                SayNextNumber
                Say "|"
                json_select "trackViewUrl"
                Replace "?uo=4" ""
                Replace "&uo=4" ""
                SayRest
                Say "|"
                json_select "artworkUrl100"
                SayRest
                Say "|"
                json_select "trackName"
                If ""
                    json_select "trackCensoredName"
                EndIf
                SayRest
                Say "|"
                json_select "artistName"
                SayRest
                Say "|"
                json_select "trackCount"
                SayNextNumber
                Say "|"
                Say "Music video"
                Say "|"
                json_select "trackExplicitness"
                Replace "notExplicit" "No"
                Replace "explicit" "Yes"
                Replace "cleaned" "Cleaned"
                SayRest
                Say "|"
                json_select "releaseDate"
                SayNChars 10
                Say "|"
                json_select "primaryGenreName"
                SayRest
                Say "|"
                json_select "copyright"
                SayRest
                Say "|"
                json_select "collectionName"
                SayRegexp "(?<=\()[^)]*(?=\))"
                Say " "
                SayRegexp "(?<=\[)[^)]*(?=\])"
                Say " "
                SayRegexp "(?<=\{)[^}]*(?=\})"
                SayNewline
            EndIf
        EndIf
    EndIf

json_foreach_end

json "off"

[ParserScriptAlbum]=...

json "on"

# debug "on" "debug-album.txt"

json_foreach "results"
    json_select "wrapperType"
    If "collection"
        json_select "collectionType"
        If "Album"

            OutputTo "ITUNESALBUMID"
            json_select "collectionId"
            SayRest

            OutputTo "ALBUMARTIST"
            json_select "artistName"
            Replace "Various Artists" ""
            Replace "Varios Artistas" ""
            Replace "Vários Artistas" ""
            Replace "Vários intérpretes" ""
            Replace "群星" ""
            Replace "群星" ""
            Replace "Eri Esittäjiä" ""
            Replace "Multi-interprètes" ""
            Replace "Verschiedene Interpreten" ""
            Replace "Verschillende artiesten" ""
            Replace "Artisti Vari" ""
            Replace "ヴァリアス・アーティスト" ""
            Replace "Diverse Artister" ""
            Replace "Разные артисты" ""
            Replace "Разные исполнители" ""
            Replace "Διάφοροι καλλιτέχνες" ""
            Replace "Blandade Artister" ""
            Replace "אמנים שונים" ""
            Replace "Çeşitli Sanatçılar" ""
            Replace "مختلف الفنانين" ""
            Replace "فنانون متنوعون" ""
            Replace "فنانون متعددون" ""
            Replace "Різні виконавці" ""
            Replace "รวมศิลปิน" ""
            Replace "Nhiều Nghệ Sĩ" ""
            SayRest

#            OutputTo "ALBUM"
#            IfVar "uncensoredTitles" "true"
#                json_select "collectionName"
#            Else
#                json_select "collectionCensoredName"
#            EndIf
#            SayRest

            OutputTo "ALBUMARTISTURL"
            json_select "artistViewUrl"
            Replace "?uo=4" ""
            Replace "&uo=4" ""
            SayRest

            OutputTo "ALBUMURL"
            json_select "collectionViewUrl"
            Replace "?uo=4" ""
            Replace "&uo=4" ""
            SayRest

            OutputTo "COVERURL"
            json_select "artworkUrl100"
            IfVar "coverartSize" "Original quality"
                Replace "://is" "://a"
                Replace "-ssl.mzstatic.com/image/thumb/" ".mzstatic.com/us/r1000/0/"
            EndIf
            RegexpReplace "(.*)\/.*" "$1"
            SayRest
            # Width x Height - JPEG Quality
            IfVar "coverartSize" "600 pixels - 50 %"
                Say "/600x600-50.jpg"
            EndIf
            IfVar "coverartSize" "600 pixels - 90 %"
                Say "/600x600-90.jpg"
            EndIf
            IfVar "coverartSize" "1200 pixels - 50 %"
                Say "/1200x1200-50.jpg"
            EndIf
            IfVar "coverartSize" "1200 pixels - 90 %"
                Say "/1200x1200-90.jpg"
            EndIf
            IfVar "coverartSize" "2400 pixels - 50 %"
                Say "/2400x2400-50.jpg"
            EndIf
            IfVar "coverartSize" "2400 pixels - 90 %"
                Say "/2400x2400-90.jpg"
            EndIf
            IfVar "coverartSize" "3600 pixels - 50 %"
                Say "/3600x3600-50.jpg"
            EndIf
            IfVar "coverartSize" "3600 pixels - 90 %"
                Say "/3600x3600-90.jpg"
            EndIf

            OutputTo "ITUNESALBUMPRICE"
            json_select "currency"
            SayRest
            Say " "
            json_select "collectionPrice"
            SayRest

            OutputTo "ALBUMADVISORY"
            json_select "contentAdvisoryRating"
            SayRest

            OutputTo "ALBUMTOTALTRACKS"
            json_select "trackCount"
            SayNextNumber

            OutputTo "COPYRIGHT"
            json_select "copyright"
            SayRest

            OutputTo "YEAR"
            json_select "releaseDate"
            SayRest

            OutputTo "ALBUMGENRE"
            json_select "primaryGenreName"
            SayRest

        EndIf
    EndIf
    If "track"

        OutputTo "ALBUM"
        IfVar "uncensoredTitles" "true"
            json_select "collectionName"
        Else
            json_select "collectionCensoredName"
        EndIf
        SayRest
        Say "|"

        OutputTo "ITUNESARTISTID"
        json_select "artistId"
        SayRest
        Say "|"

        OutputTo "ITUNESCATALOGID"
        json_select "trackId"
        SayRest
        Say "|"

        OutputTo "ARTIST"
        json_select "artistName"
        SayRest
        Say "|"

        OutputTo "TRACKS"
        IfVar "uncensoredTitles" "true"
            json_select "trackName"
        Else
            json_select "trackCensoredName"
        EndIf
        SayRest
        Say "|"

        OutputTo "ARTISTURL"
        json_select "artistViewUrl"
        Replace "?uo=4" ""
        Replace "&uo=4" ""
        SayRest
        Say "|"

        OutputTo "TRACKURL"
        json_select "trackViewUrl"
        Replace "?uo=4" ""
        Replace "&uo=4" ""
        SayRest
        Say "|"

        OutputTo "PREVIEWURL"
        json_select "previewUrl"
        Replace "?uo=4" ""
        Replace "&uo=4" ""
        SayRest
        Say "|"

        OutputTo "ITUNESTRACKPRICE"
        json_select "currency"
        SayRest
        Say " "
        json_select "trackPrice"
        SayRest
        Say "|"

        OutputTo "ITUNESADVISORY"
        json_select "trackExplicitness"
        Replace "cleaned" "2"
        Replace "explicit" "1"
        Replace "notExplicit" "0"
        SayRest
        Say "|"

        OutputTo "TRACKYEAR"
        json_select "releaseDate"
        SayRest
        Say "|"

        OutputTo "TOTALDISCS"
        json_select "discCount"
        SayNextNumber
        Say "|"

        OutputTo "DISCNUMBER"
        json_select "discNumber"
        SayNextNumber
        Say "|"

        OutputTo "TOTALTRACKS"
        json_select "trackCount"
        SayNextNumber
        Say "|"

        OutputTo "TRACK"
        json_select "trackNumber"
        SayNextNumber
        Say "|"

        OutputTo "_LENGTH"
        json_select "trackTimeMillis"
        SayNextNumber
        Say "|"

        OutputTo "GENRE"
        json_select "primaryGenreName"
        SayRest
        Say "|"

        OutputTo "ITUNESMEDIATYPE"
        json_select "kind"
        If "music-video"
            Say "Music Video"
            Say "|"
        EndIf
        If "song"
            Say "Normal"
            Say "|"
        EndIf

    EndIf
json_foreach_end

json "off"
