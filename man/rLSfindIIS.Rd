\name{rLSfindIIS}
\alias{rLSfindIIS}

\title{Find an irreducibly inconsistent set (IIS) of constraints for an infeasible model.}

\description{
 R interface function for LINDO API function \code{LSfindIIS}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSfindIIS(model,nLevel)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nLevel}{The level of analysis in finding the IIS. Bit mask values are:
                 \itemize{            
                    \item{LS_NECESSARY_ROWS} { = 1}
                    \item{LS_NECESSARY_COLS} { = 2}
                    \item{LS_SUFFICIENT_ROWS} { = 4}
                    \item{LS_SUFFICIENT_COLS} { = 8}
                  }
               }
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
