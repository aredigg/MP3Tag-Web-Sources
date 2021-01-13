# iTunes API/Apple Music parser for MP3Tag v3
[Name]=Apple Music
[BasedOn]=https://itunes.apple.com/
[AlbumUrl]=
[WordSeparator]=+
[IndexFormat]=%_url%|%Artist%|%Album%|%_preview%|%Version%|%Tracks%|%Copyright%|%Store%|%Year%|%Genre%
[Encoding]=url-utf-8

[ParserScriptIndex]=...

json "on"

json_select "resultCount"
IfNot "0"
	json_foreach "results"
	json_select "collectionType"
	If "Album"

		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		Replace "&uo=4" ""
		SayRest
		Say "|"

		json_select "artistName"
		SayRest
		Say "|"

		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf
		SayRest
		Say "|"

		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		Replace "&uo=4" ""
		SayRest
		Say "|"

		json_select "collectionExplicitness"
		Replace "notExplicit" ""
		Replace "explicit" "Explicit"
		Replace "cleaned" "Cleaned"
		SayRest
		Say "|"

		json_select "trackCount"
		SayNextNumber
		Say "|"

		json_select "copyright"
		SayRest
		Say "|"

		json_select "country"
		SayRest
		Say "|"

		json_select "releaseDate"
		SayNextNumber
		Say "|"

		json_select "primaryGenreName"
		SayRest
		SayNewline

	EndIf
	json_foreach_end
EndIf

[ParserScriptAlbum]=...

FindLine "<script type=\"fastboot/shoebox\" id=\"shoebox-media-api-cache-amp-music\">"
FindInLine "<script type=\"fastboot/shoebox\" id=\"shoebox-media-api-cache-amp-music\">"
RegexpReplace "(?i).*?id=\"shoebox-media-api-cache-amp-music\">(\{.*\"\})<\/script>.+" "$1"
Replace "\\\\\\\"" "\u0022"
Replace "\\\"" "\""
Replace "\":\"{" "\":{"
Replace "}}]}\"" "}}]}"
Replace "]}}}]}\"}" "]}}}]}}"
RegexpReplace "\.catalog\.(.*?)\.albums\.(.*?)\.art" "mp3tagalbum"
Replace ".5burl.5d.f.extend.5balbums.5d.editorialartwork.extend.offers" ""
Replace ".2cpopularity.2ceditorialvideo.fields.5balbums.3aalbums.5d.artistname" ""
Replace ".2cartisturl.2cartwork" ""
Replace ".2ccontentrating.2ceditorialartwork" ""
Replace ".2ceditorialnotes" ""
Replace ".2cname.2cplayparams.2creleasedate" ""
Replace ".2curl.fields.5bartists.5d.name.2curl.fields.5brecord-labels" ""
Replace ".5d.name.2curl.include.5bsongs.5d.artists.2ccomposers.include.tracks" ""
RegexpReplace "2crecord-labels\.l\.(.*?)\.omit" "locale"
Replace ".2cartists.locale.5bresource" ""
Replace ".5d.autos.views.appears-on.2cmore-by-artist.2crelated-videos" ""
Replace ".2cother-versions.2cyou-might-also-like.2cvideo-extras.2caudio-extras" ""

RegexpReplace "storefronts\.(.*?)\"" "storefronts\""

json "on" "current"

debug "on" "C:\debug-album.txt"
DebugWriteInput "C:\debug-album-in.txt"

json_unselect_object
json_select "mp3tagalbum"
json_select_array "d" 1
json_select "type"
If "albums"
	json_select "id"
	OutputTo "plID"
	SayRest
	json_select_object "attributes"

		json_select_object "artwork"
			json_select "url"
			IfNot ""
				Replace "{w}" "10000"
				Replace "{h}" "10000"
				Replace "{f}" "jpg"
				OutputTo "COVERURL"
				SayRest
			EndIf
		json_unselect_object

		json_select "artistName"
		OutputTo "ALBUMARTIST"
		SayRest

		json_select "isSingle"
		OutputTo "SINGLE"
		SayRest

		json_select_array "genreNames" -1 ", "
		OutputTo "AMGENRES"
		SayRest

		json_select "trackCount"
		OutputTo "TOTALTRACKS"
		SayNextNumber

		json_select "releaseDate"
		OutputTo "YEAR"
		SayRest

		json_select "name"
		OutputTo "ALBUM"
		SayRest

		json_select "recordLabel"
		OutputTo "LABEL"
		SayRest

		json_select "copyright"
		OutputTo "COPYRIGHT"
		SayRest

		json_select_object "playParams"
			IfNot ""
				json_select "id"
				OutputTo "plID2"
				SayNextNumber
				json_unselect_object
			EndIf

		json_select_object "editorialNotes"
			IfNot ""
			json_select "short"
			OutputTo "COMMENT"
			SayRest
			json_select "standard"
			OutputTo "DESCRIPTION"
			SayRest
			json_unselect_object
			EndIf

		json_select "isCompilation"
		OutputTo "COMPILATION"
		SayRest

		json_select "contentRating"
		IfNot ""
			Replace "notExplicit" "0"
			Replace "explicit" "1"
			Replace "cleaned" "2"
			OutputTo "ALBUMADVISORY"
			SayRest
		EndIf

	json_unselect_object

	json_select_object "relationships"
		json_select_object "tracks"
			json_foreach "data"
				json_select "type"
				If "songs"

					json_select "id"
					OutputTo "ITUNESCATALOGID"
					SayNextNumber
					Say "|"

					json_select_object "attributes"

						json_select "artistName"
						OutputTo "ARTIST"
						SayRest
						Say "|"

						json_select "discNumber"
						OutputTo "DISCNUMBER"
						SayNextNumber
						Say "|"

						json_select_array "genreNames" 1
						OutputTo "GENRE"
						SayRest
						Say "|"

						json_select_array "genreNames" -1 ", "
						OutputTo "GENRES"
						SayRest
						Say "|"

						json_select "durationInMillis"
						OutputTo "_LENGTH"
						SayNextNumber
						Say "|"

						json_select "releaseDate"
						OutputTo "TRACKYEAR"
						SayRest
						Say "|"

						json_select "name"
						OutputTo "TRACKS"
						SayRest
						Say "|"

						json_select "isrc"
						OutputTo "ISRC"
						SayRest
						Say "|"

						json_select "hasLyrics"
						OutputTo "AMLYRICS"
						SayRest
						Say "|"

						json_select "trackNumber"
						OutputTo "TRACK"
						SayNextNumber
						Say "|"

						json_select "audioLocale"
						OutputTo "LANGUAGE"
						SayRest
						Say "|"

						json_select "workName"
						IfNot ""
							OutputTo "SHOWMOVEMENT"
							Say "1"
							Say "|"
							OutputTo "WORK"
							SayRest
							Say "|"
							OutputTo "MOVEMENTNAME"
							json_select "name"
							FindInLine ": " 1 1
							SayRest
							Say "|"
						Else
							OutputTo "SHOWMOVEMENT"
							Say "0"
							Say "|"
							OutputTo "WORK"
							Say "|"
							OutputTo "MOVEMENTNAME"
							Say "|"
						EndIf

						json_select "composerName"
						OutputTo "COMPOSER"
						SayRest
						Say "|"

						json_select "attribution"
						OutputTo "ATTRIBUTION"
						SayRest
						Say "|"

						json_select "contentRating"
						OutputTo "ITUNESADVISORY"
						IfNot ""
							Replace "notExplicit" "0"
							Replace "explicit" "1"
							Replace "cleaned" "2"
							SayRest
						Else
							Say "0"
						EndIf
						Say "|"

					json_unselect_object
					json_select_object "relationships"

						json_select_object "composers"
							json_select_many "data" "id" ", "
							OutputTo "cmID"
							IfNot ""
								SayRest
							EndIf
							Say "|"
						json_unselect_object

						json_select_object "artists"
							json_select_many "data" "id" ", "
							OutputTo "atID"
							IfNot ""
								SayRest
							EndIf
							Say "|"
						json_unselect_object

					json_unselect_object
				EndIf
			json_foreach_end
		json_unselect_object
	json_unselect_object
EndIf
