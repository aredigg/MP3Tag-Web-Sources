# iTunes API/Apple Music parser v 3.0β for MP3Tag v3
# © 2021-2022 All Rights Reserved
[Name]=Apple Music
[BasedOn]=https://music.apple.com/
[AlbumUrl]=
[WordSeparator]=+
[IndexFormat]=%_url%|%Artist%|%Album%|%_preview%|%Version%|%Tracks%|%Collection ID%|%Copyright%|%Store%|%Currency%|%Price%|%Year%|%Genre%
[Encoding]=url-utf-8

[ParserScriptIndex]=...

json "on"

# debug "on" "debug-index.txt"

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

		json_select "collectionId"
		SayNextNumber
		Say "|"

		json_select "copyright"
		SayRest
		Say "|"

		json_select "country"
		SayRest
		Say "|"

		json_select "currency"
		SayRest
		Say "|"

		json_select "collectionPrice"
		SayRest
		Say "|"

		json_select "releaseDate"
		SayNextNumber
		Say "|"

		json_select "primaryGenreName"
		SayRest
		SayNewline

	EndIf
	If "Compilation"

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
		Replace "notExplicit" "C"
		Replace "explicit" "C Explicit"
		Replace "cleaned" "C Cleaned"
		SayRest
		Say "|"

		json_select "trackCount"
		SayNextNumber
		Say "|"

		json_select "collectionId"
		SayNextNumber
		Say "|"

		json_select "copyright"
		SayRest
		Say "|"

		json_select "country"
		SayRest
		Say "|"

		json_select "currency"
		SayRest
		Say "|"

		json_select "collectionPrice"
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

FindLine "<script type=\"application/json\" id=\"serialized-server-data\">"

RegexpReplace ".*<script type=\"application/json\" id=\"serialized-server-data\">\[(.*)\]<\/script>.*" "$1"

json "on" "current"

# debug "on" "debug-album.txt"

json_select_object "intent"
IfNot ""
	json_select_object "contentDescriptor"
	IfNot ""
		json_select "kind"
		If "album"
			json_select_object "identifiers"
			IfNot ""
				json_select "storeAdamID"
				IfNot ""
					OutputTo "ITUNESALBUMID"
					SayRest
				EndIf
				json_unselect_object
			EndIf
			json_select_object "locale"
			IfNot ""
				json_select "storefront"
				IfNot ""
					Replace "br" "143503"
					Replace "cn" "143465"
					Replace "dk" "143458"
					Replace "fi" "143447"
					Replace "fr" "143442"
					Replace "de" "143443"
					Replace "in" "143467"
					Replace "it" "143450"
					Replace "jp" "143462"
					Replace "kr" "143466"
					Replace "no" "143457"
					Replace "pl" "143478"
					Replace "pt" "143453"
					Replace "ru" "143469"
					Replace "es" "143454"
					Replace "se" "143456"
					Replace "tr" "143480"
					Replace "ae" "143481"
					Replace "gb" "143444"
					Replace "ua" "143492"
					Replace "us" "143441"
					Replace "vn" "143471"
					OutputTo "ITUNESCOUNTRYID"
					SayNextNumber
				EndIf
				json_select "language"
				IfNot ""
					OutputTo "ITUNESLANGUAGEID"
					SayRest
				EndIf
				json_unselect_object
			EndIf
		EndIf
		json_unselect_object
	EndIf
	json_unselect_object
EndIf

json_select_object "data"
IfNot ""
	json_foreach "sections"
	
		json_select "itemKind"
		If "containerDetailHeaderLockup"
			json_foreach "items"
			
				json_select_object "artwork"
				IfNot ""
					json_select_object "dictionary"
					IfNot ""
						# LQ Cover
						json_select "url"
						IfNot ""
							RegexpReplace "(.*)\/.*" "$1"
							OutputTo "COVERURL"
							SayRest
							Say "/2400x2400-50.jpg"
						EndIf
						# HQ Cover
#						json_select "url"
#						IfNot ""
#							Replace "://is" "://a"
#							Replace "-ssl.mzstatic.com/image/thumb/" ".mzstatic.com/us/r1000/0/"
#							RegexpReplace "(.*)\/.*" "$1"
#							OutputTo "COVERURL"
#							SayRest
#						EndIf
						json_unselect_object
					EndIf
					json_unselect_object
				EndIf
				
				OutputTo "ALBUM"
				json_select "title"
				Replace " - Single" ""
				RegexpReplace "\(.*\)" ""
				RegexpReplace "\[.*\]" ""
				SayRest
				
				OutputTo "SUBALBUM"
				json_select "title"
				SayRegexp "(?<=\[)[^)]*(?=\])"
				IfOutput "SUBALBUM"
					Say "\\\\"
				EndIf
				SayRegexp "(?<=\()[^)]*(?=\))"
				
				json_foreach "subtitleLinks"
					json_select "title"
					OutputTo "SUBALBUMARTIST"
					IfOutput "AM_TEMP_1"
						Say "\\\\"
					EndIf
					SayRest
					Set "AM_TEMP_1" "X"
					json_select_object "segue"
					IfNot ""
						json_select_object "destination"
						IfNot ""
							json_select_object "contentDescriptor"
							IfNot ""
								json_select "kind"
								If "artist"
									json_select_object "identifiers"
									IfNot ""
										json_select "storeAdamID"
										OutputTo "ITUNESARTISTID"
										IfOutput "AM_TEMP_2"
											Say "\\\\"
										EndIf
										SayNextNumber
										Set "AM_TEMP_2" "X"
										json_unselect_object
									EndIf
								EndIf
								json_unselect_object
							EndIf
							json_unselect_object
						EndIf
						json_unselect_object
					Else
						Set "COMPILATION"
						OutputTo "COMPILATION"
						Say "1"
					EndIf
				json_foreach_end
				Set "AM_TEMP_1"
				Set "AM_TEMP_2"
					
				json_select_object "modalPresentationDescriptor"
				IfNot ""
					OutputTo "HEADER"
					json_select "headerTitle"
					SayRest
					OutputTo "SUBHEADER"
					json_select "headerSubtitle"
					SayRest
					OutputTo "DESCRIPTION"
					json_select "paragraphText"
					SayRest
					json_unselect_object
				EndIf
				
				OutputTo "TOTALTRACKS"
				json_select "trackCount"
				SayNextNumber
				
				OutputTo "ALBUMADVISORY"
				json_select "showExplicitBadge"
				SayNextNumber
				
			json_foreach_end
		EndIf
		
		If "containerDetailTracklistFooterLockup"
			json_foreach "items"
			
				OutputTo "COPYRIGHT"
				json_select "description"
				SayRegexp "℗.*"
				If ""
					json_select "description"
					SayRegexp "©.*"
				EndIf
				
				json_select_object "linkSection"
				IfNot ""
					json_select "title"
					If "RECORD LABEL"
						OutputTo "PUBLISHER"				
					Else
						OutputTo "LINKSECTION"
					EndIf
					json_select_object "link"
					IfNot ""
						json_select "title"
						SayRest
						json_select_object "segue"
						IfNot ""
							json_select_object "destination"
							IfNot ""
								json_select_object "intent"
								IfNot ""
									json_select_object "contentDescriptor"
									IfNot ""
										json_select_object "identifiers"
										IfNot ""
											json_select "storeAdamID"
											OutputTo "ITUNESPUBLISHERID"
											SayNextNumber
											json_unselect_object
										EndIf
										json_unselect_object
									EndIf
									json_unselect_object
								EndIf
								json_unselect_object
							EndIF
							json_unselect_object
						EndIf
						json_unselect_object
					EndIf
					json_unselect_object
				EndIf
				
			json_foreach_end
		EndIf

		If "trackLockup"
			json_foreach "items"
				
				OutputTo "TRACKS"
				json_select "title"
				RegexpReplace "\(.*\)" ""
				RegexpReplace "\[.*\]" ""
				SayRest
				Say "|"
				
				OutputTo "SUBTRACK"
				json_select "title"
				SayRegexp "(?<=\[)[^)]*(?=\])"
				IfOutput "SUBTRACK"
					Say "\\\\"
				EndIf
				SayRegexp "(?<=\()[^)]*(?=\))"
				Say "|"

				OutputTo "TRACK"
				json_select "trackNumber"
				SayNextNumber
				Say "|"

				OutputTo "_LENGTH"
				json_select "duration"
				SayNextNumber
				Say "|"

				json_select_object "contentDescriptor"
				IfNot ""
					json_select "kind"
					OutputTo "ITUNESMEDIATYPE"
					If "song"
						Say "Normal"
					EndIf
					If "musicVideo"
						Say "Music Video"
					EndIf
					json_select_object "identifiers"
					IfNot ""
						OutputTo "ITUNESCATALOGID"
						json_select "storeAdamID"
						SayNextNumber
						json_unselect_object
					EndIf
					json_unselect_object
				EndIf
				OutputTo "ITUNESMEDIATYPE"
				Say "|"
				OutputTo "ITUNESCATALOGID"
				Say "|"

				json_foreach "subtitleLinks"
					json_select "title"
					OutputTo "SUBARTIST"
					IfOutput "AM_TEMP_1"
						Say "\\\\"
					EndIf
					SayRest
					Set "AM_TEMP_1" "X"
					json_select_object "segue"
					IfNot ""
						json_select_object "destination"
						IfNot ""
							json_select_object "contentDescriptor"
							IfNot ""
								json_select "kind"
								If "artist"
									json_select_object "identifiers"
									IfNot ""
										json_select "storeAdamID"
										OutputTo "ITUNESARTISTID"
										IfOutput "AM_TEMP_2"
											Say "\\\\"
										EndIf
										SayNextNumber
										Set "AM_TEMP_2" "X"
										json_unselect_object
									EndIf
								EndIf
								json_unselect_object
							EndIf
							json_unselect_object
						EndIf
						json_unselect_object
					EndIf
				json_foreach_end
				OutputTo "SUBARTIST"
				Say "|"
				OutputTo "ITUNESARTISTID"
				Say "|"
				Set "AM_TEMP_1"
				Set "AM_TEMP_2"

				
				OutputTo "COMPOSER"
				json_select "composer"
				SayRest
				Say "|"

				OutputTo "DISCNUMBER"
				json_select "discNumber"
				SayNextNumber
				Say "|"

				OutputTo "TOTALDISCS"
				json_select "discNumber"
				Set "TOTALDISCS"
				SayNextNumber

				OutputTo "ARTIST"
				json_select "artistName"
				SayRest
				Say "|"

				OutputTo "ALBUMARTIST"
				json_select "containerArtistName"
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
				Say "|"
				
			json_foreach_end
		EndIf
		
	json_foreach_end
	
	json_select_object "data" # This must be a bug in mp3tag json parser
	
	json_select_object "seoData"
	IfNot ""
		
		OutputTo "YEAR"
		json_select "musicReleaseDate"
		SayRest
		
		OutputTo "COMMENT"
		json_select "socialDescription"
		SayRest
		SayNewline
		json_select "socialTitle"
		SayRest

		json_foreach "ogSongs"
			json_select_object "attributes"
			IfNot ""
				OutputTo "TRACKYEAR"
				json_select "releaseDate"
				SayRest
				Say "|"
	
				OutputTo "ISRC"
				json_select "isrc"
				SayRest
				Say "|"
	
				# LQ Cover	
				OutputTo "TRACKCOVERURL"
				json_select_object "artwork"
				IfNot ""
					json_select "url"
					IfNot ""
						RegexpReplace "(.*)\/.*" "$1"
						SayRest
						Say "/2400x2400-50.jpg"
					EndIf
					json_unselect_object
				EndIf
				Say "|"

				# HQ Cover	
#				OutputTo "TRACKCOVERURL"
#				json_select_object "artwork"
#				IfNot ""
#					json_select "url"
#					IfNot ""
#						Replace "://is" "://a"
#						Replace "-ssl.mzstatic.com/image/thumb/" ".mzstatic.com/us/r1000/0/"
#						RegexpReplace "(.*)\/.*" "$1"
#						SayRest
#					EndIf
#					json_unselect_object
#				EndIf
#				Say "|"

				OutputTo "LANGUAGE"
				json_select "audioLocale"
				SayRest
				Say "|"
	
				OutputTo "GENRE"
				json_select_array "genreNames" 1
				SayRest
				Say "|"
				
				OutputTo "GENRES"
				json_select_array "genreNames" -1 ", "
				Replace ", Music" ""
				Replace ", Musiikki" ""
				Replace ", Musik" ""
				Replace ", Musikk" ""
				Replace ", Musique" ""
				Replace ", Muzyka" ""
				Replace ", Müzik" ""
				Replace ", Música" ""
				Replace ", Музика" ""
				SayRest
				Say "|"
				
				OutputTo "ATTRIBUTION"
				json_select "attribution"
				SayRest
				Say "|"

				OutputTo "SHOWMOVEMENT"
				json_select "workName"
				IfNot ""
					Say "1"
				EndIf
				Say "|"
			
				OutputTo "WORK"
				json_select "workName"
				SayRest
				Say "|"
				
				OutputTo "MOVEMENTNAME"
				json_select "movementName"
				SayRest
				Say "|"
				
				OutputTo "MOVEMENT"
				json_select "movementNumber"
				SayNextNumber
				Say "|"
			
				OutputTo "MOVEMENTTOTAL"
				json_select "movementCount"
				SayNextNumber
				Say "|"

				OutputTo "ITUNESADVISORY"
				json_select "contentRating"
				IfNot ""
					Replace "notExplicit" "0"
					Replace "explicit" "1"
					Replace "cleaned" "2"
					Replace "clean" "2"
					SayRest
				Else
					Say "0"
				EndIf
				Say "|"

				json_unselect_object
			EndIf
		json_foreach_end
		
		json_unselect_object
	EndIf
	
	json_unselect_object
EndIf
